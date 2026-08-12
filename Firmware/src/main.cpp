/*
  Emergency Light Health Monitor
  Clean portfolio version of firmware I originally developed for the project.

  Main functions:
  - ESP32 + SIM800 cellular connection
  - AWS IoT / MQTT communication
  - BH1750 light measurement
  - Relay control for emergency-light testing
  - Saved installation details in ESP32 NVS
  - Simple remote commands

  I have removed private certificates, keys and project credentials from
  this public version. They are loaded from secrets.h instead.
*/

#define TINY_GSM_MODEM_SIM800

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <TinyGsmClient.h>
#include <SSLClient.h>
#include <PubSubClient.h>
#include <Preferences.h>
#include <BluetoothSerial.h>
#include <esp_system.h>

#include "certificates.h"
#include "secrets.h"

// -------------------------
// Hardware
// -------------------------

constexpr int MODEM_RST      = 25;
constexpr int MODEM_POWER_ON = 23;
constexpr int MODEM_TX       = 17;
constexpr int MODEM_RX       = 16;

constexpr int STATUS_LED     = 15;
constexpr int GPRS_LED       = 13;
constexpr int TEST_RELAY     = 2;

constexpr int I2C_SDA        = 18;
constexpr int I2C_SCL        = 19;

// -------------------------
// Main objects
// -------------------------

HardwareSerial SerialAT(1);
TinyGsm modem(SerialAT);
TinyGsmClient gsmClient(modem);

SSLClient secureClient(gsmClient, TAs, (size_t)TAs_NUM, 36);
PubSubClient mqtt(secureClient);

BH1750 lightMeter;
Preferences preferences;
BluetoothSerial SerialBT;

// -------------------------
// Saved device information
// -------------------------

String deviceId;
String customerId;
String locationId;
String floorId;
String lightNumber;
String installDate;
String miscInfo;
String firmwareVersion;

// -------------------------
// MQTT topics
// -------------------------

const char* CONTROL_TOPIC = "esp/output1";
const char* RESULT_TOPIC  = "esp/lightlevel";

// -------------------------
// Function declarations
// -------------------------

void loadDeviceSettings();
void saveDeviceSetting(const String& key, const String& value);

bool connectMobileNetwork();
bool connectMqtt();

void mqttCallback(char* topic, byte* payload, unsigned int length);
void handleDeviceCommand(const String& message);

void runLightTest(const char* testName, bool relayOn);
void publishTestResult(const char* testName, float lux, int signalStrength);

String getDeviceId();
String payloadToString(byte* payload, unsigned int length);


// ============================================================
// Setup
// ============================================================

void setup()
{
    Serial.begin(115200);
    delay(100);

    pinMode(MODEM_RST, OUTPUT);
    pinMode(MODEM_POWER_ON, OUTPUT);
    pinMode(STATUS_LED, OUTPUT);
    pinMode(GPRS_LED, OUTPUT);
    pinMode(TEST_RELAY, OUTPUT);

    digitalWrite(MODEM_RST, HIGH);
    digitalWrite(MODEM_POWER_ON, HIGH);
    digitalWrite(TEST_RELAY, LOW);

    Wire.begin(I2C_SDA, I2C_SCL);
    lightMeter.begin();

    // I use Bluetooth as a simple local diagnostic link during bring-up.
    SerialBT.begin("EmergencyLightMonitor");

    // I use the ESP32 hardware ID to give each installed unit a unique MQTT ID.
    deviceId = getDeviceId();

    preferences.begin("deviceDetail", false);
    loadDeviceSettings();

    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
    delay(3000);

    SSLClientParameters clientCertificate =
        SSLClientParameters::fromPEM(
            AWS_DEVICE_CERT,
            sizeof(AWS_DEVICE_CERT),
            AWS_PRIVATE_KEY,
            sizeof(AWS_PRIVATE_KEY)
        );

    secureClient.setMutualAuthParams(clientCertificate);

    mqtt.setServer(AWS_IOT_ENDPOINT, 8883);
    mqtt.setCallback(mqttCallback);
    mqtt.setBufferSize(1024);

    connectMobileNetwork();
    connectMqtt();

    Serial.println("Setup complete.");
}


// ============================================================
// Main loop
// ============================================================

void loop()
{
    if (!modem.isGprsConnected()) {
        digitalWrite(GPRS_LED, LOW);
        connectMobileNetwork();
    } else {
        digitalWrite(GPRS_LED, HIGH);
    }

    if (!mqtt.connected()) {
        digitalWrite(STATUS_LED, LOW);
        connectMqtt();
    } else {
        digitalWrite(STATUS_LED, HIGH);
    }

    mqtt.loop();
}


// ============================================================
// Mobile network
// ============================================================

bool connectMobileNetwork()
{
    Serial.println("Connecting to mobile network...");

    if (!modem.restart()) {
        Serial.println("Modem restart failed.");
        return false;
    }

    if (!modem.gprsConnect(APN, APN_USER, APN_PASSWORD)) {
        Serial.println("GPRS connection failed.");
        return false;
    }

    Serial.println("Mobile network connected.");
    return true;
}


// ============================================================
// MQTT / AWS IoT
// ============================================================

bool connectMqtt()
{
    if (!modem.isGprsConnected()) {
        return false;
    }

    Serial.println("Connecting to AWS IoT...");

    if (!mqtt.connect(deviceId.c_str())) {
        Serial.print("MQTT connection failed. State = ");
        Serial.println(mqtt.state());
        return false;
    }

    mqtt.subscribe(CONTROL_TOPIC);

    // Each unit also listens to a topic matching its own ID.
    mqtt.subscribe(deviceId.c_str());

    Serial.println("AWS IoT connected.");
    return true;
}


void mqttCallback(char* topic, byte* payload, unsigned int length)
{
    String message = payloadToString(payload, length);
    message.trim();

    Serial.print("MQTT topic: ");
    Serial.println(topic);

    Serial.print("MQTT message: ");
    Serial.println(message);

    // The common control topic starts and stops the emergency-light tests.
    if (String(topic) == CONTROL_TOPIC) {
        if (message == "0") {
            runLightTest("30min", true);
        }
        else if (message == "1") {
            runLightTest("3Hr", true);
        }
        else if (message == "2") {
            runLightTest("Day", true);
        }
        else if (message == "3") {
            runLightTest("30min Test End", false);
        }
        else if (message == "4") {
            runLightTest("3Hr Test End", false);
        }
        else if (message == "5") {
            runLightTest("Day Test End", false);
        }

        return;
    }

    // Installation details are only changed through this unit's own topic.
    if (String(topic) == deviceId) {
        handleDeviceCommand(message);
    }
}


// ============================================================
// Device commands
// ============================================================

void handleDeviceCommand(const String& message)
{
    if (message.equalsIgnoreCase("restart")) {
        Serial.println("Remote restart requested.");
        delay(500);
        ESP.restart();
    }

    int separator = message.indexOf(' ');

    if (separator < 0) {
        Serial.println("Command ignored - expected 'key value'.");
        return;
    }

    String key = message.substring(0, separator);
    String value = message.substring(separator + 1);

    key.toLowerCase();
    value.trim();

    if (key == "loc") {
        saveDeviceSetting("location", value);
    }
    else if (key == "cus") {
        saveDeviceSetting("customer", value);
    }
    else if (key == "flr") {
        saveDeviceSetting("floor", value);
    }
    else if (key == "num") {
        saveDeviceSetting("number", value);
    }
    else if (key == "ins") {
        saveDeviceSetting("install", value);
    }
    else if (key == "mis") {
        saveDeviceSetting("misc", value);
    }
    else if (key == "ver") {
        saveDeviceSetting("version", value);
    }
    else {
        Serial.println("Unknown device command.");
        return;
    }

    // I restart after changing installation data so the unit comes back
    // with one clean set of saved values.
    delay(500);
    ESP.restart();
}


// ============================================================
// Emergency-light test
// ============================================================

void runLightTest(const char* testName, bool relayOn)
{
    digitalWrite(TEST_RELAY, relayOn ? HIGH : LOW);
    delay(100);

    float lux = lightMeter.readLightLevel();
    int signalStrength = modem.getSignalQuality();

    publishTestResult(testName, lux, signalStrength);
}


void publishTestResult(const char* testName, float lux, int signalStrength)
{
    char message[512];

    String gsmTime = modem.getGSMDateTime(DATE_TIME);
    String gsmDate = modem.getGSMDateTime(DATE_DATE);

    snprintf(
        message,
        sizeof(message),
        "{"
        "\"ID\":\"%s\","
        "\"Cus\":\"%s\","
        "\"Loc\":\"%s\","
        "\"Flr\":\"%s\","
        "\"Num\":\"%s\","
        "\"Time\":\"%s\","
        "\"Date\":\"%s\","
        "\"InstallDate\":\"%s\","
        "\"Misc\":\"%s\","
        "\"Ver\":\"%s\","
        "\"Test\":\"%s\","
        "\"Lux\":%.1f,"
        "\"SigS\":%d"
        "}",
        deviceId.c_str(),
        customerId.c_str(),
        locationId.c_str(),
        floorId.c_str(),
        lightNumber.c_str(),
        gsmTime.c_str(),
        gsmDate.c_str(),
        installDate.c_str(),
        miscInfo.c_str(),
        firmwareVersion.c_str(),
        testName,
        lux,
        signalStrength
    );

    if (mqtt.publish(RESULT_TOPIC, message)) {
        Serial.print("Published: ");
        Serial.println(message);
    } else {
        Serial.println("MQTT publish failed.");
    }
}


// ============================================================
// Saved installation information
// ============================================================

void loadDeviceSettings()
{
    customerId      = preferences.getString("customer", "default");
    locationId      = preferences.getString("location", "useEirCode");
    floorId         = preferences.getString("floor", "Floor");
    lightNumber     = preferences.getString("number", "Num");
    installDate     = preferences.getString("install", "InstallDate");
    miscInfo        = preferences.getString("misc", "Sundries");
    firmwareVersion = preferences.getString("version", "Version");

    Serial.println("Loaded saved device information.");
}


void saveDeviceSetting(const String& key, const String& value)
{
    preferences.putString(key.c_str(), value);

    Serial.print("Saved ");
    Serial.print(key);
    Serial.print(": ");
    Serial.println(value);
}


// ============================================================
// Helpers
// ============================================================

String getDeviceId()
{
    uint64_t chipId = ESP.getEfuseMac();

    char id[20];

    snprintf(
        id,
        sizeof(id),
        "%04X%08X",
        (uint16_t)(chipId >> 32),
        (uint32_t)chipId
    );

    return String(id);
}


String payloadToString(byte* payload, unsigned int length)
{
    String message;
    message.reserve(length);

    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    return message;
}
