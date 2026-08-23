# PCB Design Evidence

I use this folder to document the PCB layout and manufacturing evidence for my Emergency Exit Light Health Checker prototype.

The PCB material shows how I moved the design from schematic capture into a manufactured prototype board. The as-built version uses an ESP32 controller, plug-in SIM800L GPRS module, BH1750 light sensor, relay switching, AC/DC conversion and separate low-voltage rails for the controller and modem.

## Included files

| File | Description |
|---|---|
| `PCB_Top_Layer.png` | Top-side PCB layout showing component placement, routing and the high-voltage / low-voltage partitioning. |
| `PCB_Bottom_Layer.png` | Bottom-side PCB layout showing routing and copper areas. |
| `Gerber_ExitLightTester_v1.0.pdf` | Gerber / layer evidence exported from the PCB design. |
| `LayerStacked.pdf` | Combined PCB layer view used to review the board stack and manufacturing output. |
| `PCB_SignOff_panelised.pdf` | Panelised PCB evidence from the board supplier / manufacturing-preparation stage. |

## Design notes

I separated the mains / relay switching area from the low-voltage ESP32, sensor and modem circuitry.

The design includes:

- AC input and relay switching area;
- AC/DC conversion and local regulation;
- 3.3 V supply for the ESP32 and digital circuitry;
- 4.1 V supply for the cellular modem;
- UART programming access;
- I²C expansion connection;
- status indication; and
- mounting / manufacturing features.

I include the panelised PCB material because it shows that the work progressed beyond schematic and layout into manufacture preparation.

## Scope

This is portfolio evidence of my PCB design and manufacturing-preparation work. It is not a certified production release, installation guide or safety-approved design package.
