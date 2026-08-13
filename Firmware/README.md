# Emergency Light Health Monitor — Firmware

This folder contains a cleaned-up portfolio version of firmware I originally developed for the emergency-light monitoring project.

The original development code grew while I was integrating the modem, AWS IoT, light sensing, relay control and remote configuration. For the portfolio version I have simplified the structure, removed old experiments and removed all private credentials so the main behaviour is easier to follow.

## What the firmware does

The ESP32:

- connects to the mobile network through a SIM800 modem;
- connects securely to AWS IoT using MQTT;
- measures emergency-light output using a BH1750 lux sensor;
- controls a relay used to start and stop an emergency-light test;
- publishes ux, signal strength, timestamp and test-state data and installation information;
- stores customer/location/floor/light information in ESP32 NVS;
- accepts simple remote configuration and restart commands; and


## Main program flow

```text
setup
  -> initialise hardware
  -> load saved installation details
  -> initialise modem
  -> connect mobile network
  -> connect AWS IoT / MQTT

loop
  -> check cellular connection
  -> check MQTT connection
  -> process MQTT messages
```

I deliberately kept the public version simple. Most of the behaviour is contained in a few functions:

- `connectMobileNetwork()`
- `connectMqtt()`
- `handleDeviceCommand()`
- `runLightTest()`
- `publishTestResult()`

## Test commands

The common MQTT control topic uses simple numeric commands:

| Command | Action |
|---|---|
| `0` | Start 30-minute test |
| `1` | Start 3-hour test |
| `2` | Start day test |
| `3` | End 30-minute test |
| `4` | End 3-hour test |
| `5` | End day test |

A separate device-specific topic is used for installation data such as location, customer, floor and light number.

## Building the project

The project uses **VS Code + PlatformIO** with the Arduino ESP32 framework.

Before building:

1. Copy `include/secrets.example.h` to `include/secrets.h`.
2. Add the APN, AWS IoT endpoint, device certificate and private key to `secrets.h`.
3. Keep `secrets.h` private. It is excluded by `.gitignore`.
4. Keep `include/certificates.h` as the public root-CA trust-anchor file used by SSLClient.

## Security note

No working private key, AWS device certificate, broker credential or production APN is included in this portfolio version.
