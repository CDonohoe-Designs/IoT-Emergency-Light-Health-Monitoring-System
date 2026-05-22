# Documentation

This folder contains the main project documentation for the Emergency Exit Light Health Checker.

The documentation gives an overview of the retrofit concept, the hardware architecture, the cloud/MQTT reporting flow, and example evidence from the prototype stage.

## Included Documents

| File | Description |
|---|---|
| `ExitLight_Health_Checker_Overview.pdf` | Main project overview covering the system concept, key components, block diagram, AWS/MQTT flow, schematic overview, PCB images, prototype images and installed retrofit example. |

## Documentation Summary

The Emergency Exit Light Health Checker was designed as a retrofit module for existing emergency exit-light fittings.

The system could initiate a remote test cycle over a cellular GPRS connection using AWS IoT/MQTT-style messaging. Once triggered, the ESP32 controlled an onboard relay to place the fitting into test mode, measured the light output using a BH1750 digital lux sensor, and returned test data to the cloud backend for reporting.

The documentation includes evidence of:

- system concept and use case
- ESP32-based controller architecture
- SIM800L GPRS communication
- BH1750 light sensing
- relay-controlled test switching
- AC/DC and low-voltage power sections
- AWS IoT/MQTT reporting concept
- prototype installation inside an emergency light unit
- example reporting and test data flow

## Note

This documentation is included as portfolio evidence of independent/freelance electronic design work. It is not intended as a certified product manual, installation guide, or safety-approved design package.
