# Cloud / MQTT Reporting Flow

This folder contains cloud-side evidence for my Emergency Exit Light Health Checker prototype.

The system was designed to send test results from the retrofit hardware to a cloud backend using a cellular GPRS connection and an AWS IoT/MQTT-style reporting flow. The cloud side was used to receive test data, process scheduled test events, and support report generation.

## Included Files

| File | Description |
|---|---|
| `AWS_System_Overview.png` | Cloud architecture overview showing MQTT, AWS IoT Core, EventBridge, Lambda, IoT Analytics-style processing, data storage and reporting flow. |
| `Example_JSON_Payload_Redacted.md` | Example of the test data packet sent from the device to the cloud backend, with customer/device details removed. |

## Cloud Flow Summary

My prototype cloud flow included:

- remote test initiation using a scheduled/cloud-side trigger
- cellular GPRS communication from the device
- MQTT-style messaging into AWS IoT Core
- AWS Lambda-style processing
- IoT Analytics-style data handling
- storage of test records
- report generation using lux level, signal strength, timestamp, test type and pass/fail result

## Example Payload

The device reported test data in a JSON-style format, including:

- device ID
- customer/site reference
- test type
- time and date
- lux reading
- signal strength
- pass/fail status

Public examples in this repository are redacted to remove customer names, device IDs, locations and account-specific details.

## Note

This folder is included as portfolio evidence of the cloud/MQTT reporting concept. It does not include private AWS credentials, certificates, endpoints or customer data.
