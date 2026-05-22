
# Firmware

This folder documents the firmware architecture for my IoT Emergency Light Health Monitoring System.

I developed the original prototype firmware using **Visual Studio Code** and **PlatformIO** for an **ESP32-based monitoring module**. I am not publishing the raw source code here because it was prototype firmware and contained project-specific credentials, cloud certificates and device configuration.

Instead, this section documents how my firmware was structured, what interfaces it used, and how it controlled the system.

## Firmware Purpose

My firmware was responsible for controlling and monitoring the emergency-light test module. It handled:

- BH1750 light sensor readings
- Relay control for discharge testing
- SIM800L cellular communication
- MQTT reporting to AWS IoT Core
- Test mode control for short, quarterly and annual checks
- Local configuration storage on the ESP32
- Status indication using LEDs

## Development Environment

- MCU: ESP32
- IDE: Visual Studio Code
- Build system: PlatformIO
- Framework: Arduino-style ESP32 firmware
- Cellular modem: SIM800L
- Cloud communication: MQTT to AWS IoT Core
- Light sensor: BH1750 over I2C
- Relay control: GPIO
- Local storage: ESP32 Preferences / NVS

## Note

The purpose of this folder is to show the firmware design intent and system behaviour without exposing prototype source code, private keys, certificates or project-specific configuration.
