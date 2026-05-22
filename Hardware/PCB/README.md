
# PCB Design Evidence

This folder contains PCB layout and manufacturing evidence for my Emergency Exit Light Health Checker prototype.

The PCB files show how I moved the design from schematic capture into a manufactured prototype board. My as-built prototype used an ESP32 controller, plug-in SIM800L GPRS module, BH1750 light sensor, relay switching, AC/DC conversion and separate low-voltage power rails for the controller and modem.

## Included Files

| File | Description |
|---|---|
| `PCB_Top_Layer.png` | Top-side PCB layout view showing my component placement, routing and high-voltage/low-voltage separation. |
| `PCB_Bottom_Layer.pngv1.0.png` | Bottom-side PCB layout view showing routing, copper areas and silkscreen information. |
| `Gerber_ExitLightTester_v1.0.pdf` | Gerber/layer evidence exported from my PCB design. |
| `LayerStacked.pdf` | Combined PCB layer/stacked view used to review the board layers and manufacturing output. |
| `PCB_SignOff_panelised.pdf` | Panelised PCB evidence from the board supplier/manufacturing preparation stage. |

## Design Notes

The PCB layout separated the mains/relay switching area from the low-voltage ESP32, sensor and modem circuitry.

My design included:

- AC input and relay switching area
- AC/DC conversion and local regulation
- 3.3 V supply for the ESP32 and digital circuitry
- 4.1 V supply for the cellular modem
- UART programming access
- I2C expansion connector
- status LEDs
- mounting holes
- panelised manufacturing output

The panelised PCB evidence is included to show that the design progressed beyond schematic/layout work and was prepared for board manufacture.

## Note

This material is included as portfolio evidence of my PCB design and manufacturing preparation work. It is not intended as a certified production release, installation guide or safety-approved design package.
