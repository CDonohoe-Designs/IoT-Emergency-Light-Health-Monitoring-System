# Emergency Light Health Monitor — Firmware

I developed this firmware for the ESP32-based Emergency Light Health Monitor prototype and later cleaned it into a simpler public portfolio version.

The original development code grew while I was integrating the modem, AWS IoT, light sensing, relay control and remote configuration. For this repository I removed old experiments and private credentials so the main behaviour is easier to review.

## What the firmware does

The ESP32:

- connects to the mobile network through a SIM800 modem;
- connects securely to AWS IoT using MQTT;
- measures emergency-light output using a BH1750 lux sensor;
- controls the relay used to start and stop an emergency-light test;
- publishes lux, signal strength, timestamp, test-state and installation metadata;
- stores customer / location / floor / light information in ESP32 NVS; and
- accepts simple remote configuration and restart commands.

The public firmware publishes measurement data. I treat **pass/fail evaluation as a cloud/reporting function** derived from those measurements rather than as a result calculated directly in the ESP32 code.

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

I kept the public version intentionally straightforward. Most of the behaviour is contained in:

- `connectMobileNetwork()`
- `connectMqtt()`
- `handleDeviceCommand()`
- `runLightTest()`
- `publishTestResult()`

## Test commands

The prototype MQTT control topic uses simple numeric commands:

| Command | Action |
|---|---|
| `0` | Start 30-minute test |
| `1` | Start 3-hour test |
| `2` | Start day / short test |
| `3` | End 30-minute test |
| `4` | End 3-hour test |
| `5` | End day / short test |

A separate device-specific topic is used for installation data such as location, customer, floor and light number.

## Building the project

I used **VS Code + PlatformIO** with the Arduino ESP32 framework.

Before building:

1. Copy `include/secrets.example.h` to `include/secrets.h`.
2. Add the APN, AWS IoT endpoint, device certificate and private key to `secrets.h`.
3. Provide an `include/certificates.h` file containing the public root-CA trust anchors required by SSLClient / the selected AWS IoT endpoint.
4. Keep private device credentials out of source control. `secrets.h`, `.key`, `.pem` and `.crt` files are excluded by `.gitignore`.

The repository includes `docs/certificates_note.md` to explain the expected `certificates.h` role without publishing account-specific or private credential material.

## Security note

I do not publish a working private key, AWS device certificate, broker credential or production APN in this portfolio version.

## Prototype limitations

The SIM800L was appropriate for the original prototype, but it relies on legacy 2G / GPRS service. For a current design I would reassess the cellular platform and consider LTE-M / NB-IoT or another technology appropriate to the deployment region.

The prototype also relies on cloud-side start and end commands for test timing. For a production design I would add a **local maximum test-duration fail-safe** in firmware so a lost end command cannot leave the relay in test mode indefinitely.
