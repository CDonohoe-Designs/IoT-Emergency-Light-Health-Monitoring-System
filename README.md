# Emergency Exit Light Health Checker

## Overview
Short 2–3 paragraph summary of what the project does.

## Why I Built It
Manual emergency light testing is time-consuming, so I designed a retrofit IoT module to automate the test and record the result.

## How It Works
Normal mode: mains power passes through the relay to the exit light.  
Test mode: the relay opens, the exit light runs from battery, the BH1750 measures lux, and the result is sent to AWS IoT.

## Key Features
- ESP32-based controller
- SIM800L GPRS modem
- BH1750 lux sensor
- Relay-controlled mains test switching
- AWS IoT / MQTT reporting
- Sample pass/fail dataset
- Custom PCB, Gerbers and panelised board evidence

## System Architecture
Add your block diagram image here.

## PCB Design
Add PCB / Gerber / panelised board images here.

## Sample Data
Add the dataset image and JSON payload.

## Skills Demonstrated
Hardware design, PCB layout, IoT, AWS, MQTT, cellular comms, sensor integration, data logging, and retrofit product development.

## Safety Note
Mention that it involves 230 VAC and would need proper compliance/testing for real deployment.
