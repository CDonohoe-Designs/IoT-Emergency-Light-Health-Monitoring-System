
# MQTT Topic Structure

This document describes the MQTT topic structure used by my prototype firmware for the IoT Emergency Light Health Monitoring System.

The original firmware used an ESP32 with a SIM800L cellular modem to connect to AWS IoT Core and exchange MQTT messages for test control, device status and light-level reporting.

The exact production credentials, AWS endpoint, certificates, private keys and APN details are not included in this repository.

## MQTT Purpose

In my design, MQTT was used for:

- Sending remote test commands to the emergency-light monitor
- Starting discharge tests
- Ending discharge tests
- Reporting light-level readings
- Reporting modem signal strength
- Sending device identity and location metadata
- Updating device configuration fields remotely

## Prototype Topic Overview

| Topic | Direction | Purpose |
|---|---|---|
| `esp/output1` | Cloud to device | General command topic used to send test-control commands |
| `esp/lightlevel` | Device to cloud | Published light-level readings, test state and device status |
| `<unique_device_id>` | Cloud to device | Device-specific command/configuration topic |
| `<customer_id>` | Cloud to device | Customer/group-specific command topic |
| `<location_id>` | Cloud to device | Location-specific command topic |
| `<floor_id>` | Cloud to device | Floor-specific command topic |
| `<unit_number>` | Cloud to device | Unit-specific command topic |
| `<misc_id>` | Cloud to device | Additional grouping/configuration topic |
| `<version_id>` | Cloud to device | Firmware/version-related grouping topic |
| `<install_date_id>` | Cloud to device | Installation-date/configuration topic |

## Device Identity

Each device used a generated unique ID so that individual emergency-light monitors could receive targeted commands.

In the prototype firmware, the ESP32 Bluetooth MAC address was used as the basis for the unique device ID.

Example format:

```text
<unique_device_id>
