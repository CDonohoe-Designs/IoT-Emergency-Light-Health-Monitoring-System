# MQTT Topic Structure

I used this topic structure in the prototype firmware for my IoT Emergency Light Health Monitoring System.

The original design used an **ESP32** with a **SIM800L cellular modem** to connect to **AWS IoT Core** and exchange MQTT messages for test control, device status and light-level reporting.

I do not publish production credentials, AWS endpoints, device certificates, private keys or APN details in this repository.

## MQTT purpose

In my prototype, MQTT was used for:

- sending remote test commands to the emergency-light monitor;
- starting and ending discharge tests;
- reporting light-level readings;
- reporting modem signal strength;
- sending device identity and location metadata; and
- updating stored device configuration remotely.

## Device identity

In the public firmware I derive the device ID from the ESP32 eFuse hardware ID.

For a production design I would use a controlled provisioning process so each unit receives a managed device identity and associated credentials during manufacture.

Example placeholder:

```text
<unique_device_id>
```

## Command topics

The main prototype command topic was:

```text
esp/output1
```

The device-specific topic was:

```text
<unique_device_id>
```

The common topic was sufficient for proving the end-to-end prototype path. For a production design I would separate commands by device and use a clearer topic hierarchy.

## Prototype command payloads

| Payload | Intended action |
|---|---|
| `0` | Start 30-minute discharge test |
| `1` | Start 3-hour discharge test |
| `2` | Start day / short monitoring test |
| `3` | End 30-minute test and return relay to normal state |
| `4` | End 3-hour test and return relay to normal state |
| `5` | End day / short test and return relay to normal state |
| `restart` | Restart the ESP32 device |

I used simple single-character commands because the priority at the prototype stage was proving the complete device-to-cloud workflow.

For a production version I would move to structured commands, for example:

```json
{
  "command": "start_test",
  "test_type": "quarterly_30_min",
  "timestamp": "YYYY-MM-DDTHH:MM:SSZ"
}
```

## Configuration update commands

The prototype also accepts simple key/value updates on the device-specific topic.

| Prefix | Purpose |
|---|---|
| `cus` | Customer ID |
| `loc` | Location ID |
| `flr` | Floor ID |
| `num` | Emergency-light unit number |
| `mis` | Miscellaneous project field |
| `ver` | Firmware / hardware version reference |
| `ins` | Installation-date reference |

Example:

```text
loc building-a
```

The ESP32 stores these values in NVS so they survive reset and power loss.

## Published status topic

The firmware publishes test and sensor data to:

```text
esp/lightlevel
```

A typical payload contains:

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

The firmware publishes the measurement data. I treat **pass/fail determination as a cloud/reporting function** derived from those measurements.

## Production improvements

If I were taking the prototype further, I would:

- use structured JSON commands;
- separate telemetry, command, acknowledgement, configuration and status topics;
- add command acknowledgements and error reporting;
- use controlled device provisioning;
- add a local maximum-test timeout / fail-safe;
- reassess the cellular platform because SIM800L relies on legacy 2G / GPRS service; and
- keep all private credentials outside source control.

A cleaner production-style topic structure could be:

```text
emergency-light/<device_id>/telemetry
emergency-light/<device_id>/command
emergency-light/<device_id>/command/ack
emergency-light/<device_id>/config
emergency-light/<device_id>/status
```
