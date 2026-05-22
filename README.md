# Emergency Exit Light Health Checker

An IoT retrofit module I developed during my freelance engineering period to automate emergency exit-light testing and remote reporting.

The system was designed to be retrofitted into an existing emergency light unit. Test cycles could be initiated remotely over the cellular GPRS link using cloud-side scheduling/AWS IoT MQTT messaging. Once triggered, the ESP32 controlled a relay to place the fitting into test mode, measured the light output during the battery discharge period, and returned lux level, signal strength, timestamp and pass/fail data to the cloud backend for reporting.


---

## Project Summary

Emergency exit lights normally require periodic testing to confirm that the internal battery can keep the fitting illuminated during a power-loss condition.

I designed a prototype health-check module that could automate this process by:

- switching the fitting into test mode using a relay
- measuring light output using a BH1750 light sensor
- using an ESP32 as the main controller
- sending test data over GPRS using a SIM800L modem
- reporting lux level, signal strength, date/time and pass/fail result
- supporting cloud-side processing using AWS IoT/MQTT services

---

## My work included:

- system concept and architecture
- schematic design
- PCB layout and manufacturing outputs
- ESP32, SIM800L and BH1750 integration
- relay-controlled emergency-light test switching
- 5 V, 3.3 V and 4.1 V power sections
- UART and I²C interfaces
- prototype assembly and installation testing
- AWS/MQTT reporting concept
- example test dataset and reporting flow

---

## Safety and Portfolio Note

This project involved mains-voltage switching and was developed as a prototype/portfolio engineering project. The repository is provided as evidence of my independent electronic design work and is not intended as a certified product design, installation guide or safety-approved design package.

## System Overview

The module monitors the health of an emergency exit light by placing the fitting into a controlled test state and measuring the resulting light output.

Typical test modes included:

- short functional test
- 30-minute discharge test
- 3-hour discharge test

The measured data was sent to the cloud and could be used to generate a pass/fail report.

---

## Hardware Overview

Main hardware blocks:

| Block | Description |
|---|---|
| Controller | ESP32 WROOM module |
| Cellular modem | SIM800L GPRS module |
| Light sensor | BH1750 digital lux sensor |
| Switching | Relay-controlled AC test switching |
| Power | AC/DC converter, 5 V rail, 3.3 V rail and 4.1 V modem rail |
| Interfaces | UART, I²C, external GPIO/I²C connector |
| Debug/programming | UART programming header, reset and boot buttons |

---

## PCB and Manufacturing Evidence

The project includes evidence of:

- schematic design
- PCB top and bottom layers
- Gerber/layer views
- panelised PCB output
- assembled prototype hardware
- installed prototype inside an emergency light fitting

Images and PDFs are included in the `Hardware/` and `Documentation/` folders.

---

## Cloud / Data Flow

The prototype used a cloud reporting concept based around:

- MQTT messaging
- AWS IoT Core
- AWS Lambda
- IoT Analytics-style processing
- stored test data
- pass/fail report generation

Example payload format:

```json
{
  "ID": "REDACTED_DEVICE_ID",
  "Cus": "REDACTED_CUSTOMER",
  "Loc": "REDACTED_LOCATION",
  "Time": "16:05:40+04",
  "Date": "22/09/22",
  "Test": "30m",
  "Lux": 154.2,
  "SigS": 15
}

## Safety and Portfolio Note

This project involved mains-voltage switching and was developed as a prototype/portfolio engineering project. The repository is provided as evidence of my independent electronic design work and is not intended as a certified product design, installation guide or safety-approved design package.
