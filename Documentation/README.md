# Documentation

I use this folder for the main project documentation for my Emergency Exit Light Health Checker prototype.

The documentation covers the retrofit concept, hardware architecture, cloud / MQTT reporting flow and representative evidence from the prototype stage.

## Included document

| File | Description |
|---|---|
| `ExitLight Health Checker_OVERVIEW.pdf` | Main project overview covering the system concept, key components, block diagram, AWS / MQTT flow, schematic overview, PCB images, prototype images and installed retrofit example. |

## What the documentation shows

The Emergency Exit Light Health Checker was designed as a retrofit module for existing emergency-light fittings.

My prototype could receive a remotely scheduled test command, use a relay to place the fitting into test mode, measure light output with a BH1750 lux sensor and return test measurements to the cloud backend for storage and reporting.

The documentation includes evidence of:

- system concept and use case;
- ESP32-based controller architecture;
- SIM800L GPRS communication;
- BH1750 light sensing;
- relay-controlled test switching;
- AC/DC and low-voltage power sections;
- AWS IoT / MQTT reporting concept;
- prototype installation inside an emergency-light fitting; and
- representative test-data and reporting flow.

## Scope

I include this material as portfolio evidence of my electronic design and system-integration work. It is not a certified product manual, installation guide or safety-approved design package.
