# Cloud / MQTT Reporting Flow

I used this folder to document the cloud-side reporting flow for my Emergency Exit Light Health Checker prototype.

The prototype sends test measurements from the retrofit hardware over a cellular GPRS connection using MQTT. I used AWS IoT services to receive the data, support scheduled test control, process the incoming measurements and feed the reporting workflow.

## Included files

| File | Description |
|---|---|
| `AWS_System_Overview.png` | My cloud architecture overview showing MQTT, AWS IoT Core, EventBridge, Lambda, IoT Analytics-style processing, data storage and reporting flow. |
| `Example_JSON_Payload_Redacted.md` | Redacted example of the test-data packet published by the device. |

## Cloud flow

My prototype cloud flow included:

- scheduled / cloud-side test initiation;
- cellular GPRS communication from the device;
- MQTT messaging into AWS IoT Core;
- Lambda-style processing;
- data handling / storage; and
- report generation from lux level, signal strength, timestamp, test type and installation metadata.

The device itself publishes measurement data. I treat **pass/fail evaluation as a cloud/reporting function** derived from those measurements rather than as a field generated directly by the ESP32 firmware.

## Example payload content

The device reports fields including:

- device ID;
- customer / site reference;
- floor / unit reference;
- test type;
- time and date;
- lux reading; and
- cellular signal quality.

Public examples are redacted to remove customer names, device IDs, locations and account-specific details.

## Scope

This folder is portfolio evidence of the MQTT / AWS IoT reporting concept I developed for the prototype. I do not publish private AWS credentials, device certificates, private keys, endpoints or customer data.
