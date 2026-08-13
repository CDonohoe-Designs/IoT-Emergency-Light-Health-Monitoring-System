
# MQTT Topic Structure

This document describes the MQTT topic structure I used in my prototype firmware for the IoT Emergency Light Health Monitoring System.

My original firmware used an **ESP32** with a **SIM800L cellular modem** to connect to **AWS IoT Core** and exchange MQTT messages for test control, device status and light-level reporting.

The production credentials, AWS endpoint, certificates, private keys and APN details are not included in this repository.

---

## MQTT Purpose

In my design, MQTT was used for:

- Sending remote test commands to the emergency-light monitor
- Starting discharge tests
- Ending discharge tests
- Reporting light-level readings
- Reporting modem signal strength
- Sending device identity and location metadata
- Updating device configuration fields remotely

---

## Device Identity

Each device used a generated unique ID so that individual emergency-light monitors could receive targeted commands.

In the prototype firmware, I used the ESP32 Bluetooth MAC address as the basis for the unique device ID.

For a production design, I would use a cleaner provisioning method where each device receives a controlled serial number or device certificate identity during manufacturing.

Example placeholder:

```text
<unique_device_id>
```

---

## Command Topics

The main prototype command topic was:

```text
esp/output1
```

This allowed a cloud-side command to trigger test behaviour across devices.

The device-specific topic was:

```text
<unique_device_id>
```

This allowed commands to target one device only.

---

## Prototype Command Payloads

The prototype firmware used simple command payloads to control test states.

| Payload | Intended Action |
|---|---|
| `0` | Start 30-minute discharge test |
| `1` | Start 3-hour discharge test |
| `2` | Start daily / short monitoring check |
| `3` | Mark 30-minute test complete / return relay to normal state |
| `4` | End 3-hour discharge test / return relay to normal state
| `5` | Mark daily test complete / return relay to normal state |
| `restart` | Restart the ESP32 device |

The original firmware used simple single-character commands because the priority at the prototype stage was proving the end-to-end system.

For a production version, I would replace these with structured JSON commands, for example:

```json
{
  "command": "start_test",
  "test_type": "quarterly_30_min",
  "requested_by": "cloud",
  "timestamp": "YYYY-MM-DDTHH:MM:SSZ"
}
```

---

## Configuration Update Commands

The prototype firmware also allowed remote updates to stored device configuration values using messages sent to the device-specific topic.

| Command Prefix | Purpose |
|---|---|
| `cus` | Update customer ID |
| `loc` | Update location ID |
| `flr` | Update floor ID |
| `num` | Update emergency-light unit number |
| `mis` | Update miscellaneous project/customer field |
| `ver` | Update firmware or hardware version reference |
| `ins` | Update installation-date reference |

Example:

```text
loc building-a
```

The ESP32 stored these values in non-volatile memory so they were retained after reset or power loss.

---

## Published Status Topic

The firmware published test and sensor data to:

```text
esp/lightlevel
```

This topic carried status data from the device back to the cloud.

---

## Example Published Payload

A typical published payload contained:

```json
{
  "ID": "<unique_device_id>",
  "Cus": "<customer_id>",
  "Loc": "<location_id>",
  "Flr": "<floor_id>",
  "Num": "<unit_number>",
  "Time": "<network_time>",
  "Date": "<network_date>",
  "InstallDate": "<install_date>",
  "Misc": "<misc_id>",
  "Ver": "<version_id>",
  "Test": "30m",
  "Lux": 123.4,
  "SigS": 18
}
```

---

## Key Data Fields

| Field | Meaning |
|---|---|
| `ID` | Unique device identity |
| `Cus` | Customer identifier |
| `Loc` | Location identifier |
| `Flr` | Floor identifier |
| `Num` | Emergency-light unit number |
| `Time` | Time from modem/network |
| `Date` | Date from modem/network |
| `InstallDate` | Stored installation reference |
| `Misc` | Additional project/customer field |
| `Ver` | Firmware or hardware version reference |
| `Test` | Current test state |
| `Lux` | BH1750 light-level reading |
| `SigS` | SIM800L cellular signal quality |

---

## Production Improvements

The prototype MQTT design proved the communication path from device to cloud, but I would improve the production version by:

- Replacing simple numeric commands with structured JSON commands
- Using clearer topic names
- Adding command acknowledgements
- Adding error codes and timeout reporting
- Separating telemetry, command and configuration topics
- Using controlled device provisioning during manufacturing
- Avoiding hard-coded credentials or certificates in source code

A cleaner production-style topic structure could be:

```text
emergency-light/<device_id>/telemetry
emergency-light/<device_id>/command
emergency-light/<device_id>/command/ack
emergency-light/<device_id>/config
emergency-light/<device_id>/status
```

---

## Notes

This document describes the MQTT design intent and prototype behaviour without publishing private credentials, certificates, endpoints or raw prototype source code.
