# Schematic

This folder contains schematic evidence for my Emergency Exit Light Health Checker hardware design.

The main schematic included here represents the as-built prototype version of my board, where I implemented the cellular connection using a plug-in SIM800L module. This matches the assembled prototype PCB and retrofit installation images shown elsewhere in the repository.

I also explored a later design variant where the SIM800C modem, SIM card holder and ESD protection were integrated directly onto the PCB. That version is included separately as a design variant and is not the same as the manufactured prototype shown in the project images.

## Included Files

| File | Description |
|---|---|
| `Schematic_ESP32_AC_SIM800L_AsBuilt_Prototype.pdf` | My as-built prototype schematic using an ESP32, plug-in SIM800L module, BH1750 light sensor, relay switching and the required power sections. |
| `Design_Variants/Schematic_ESP32_SIM800C_OnPCB_Concept.pdf` | A later concept/design variant where I explored integrating the SIM800C modem, SIM card holder and ESD protection directly onto the PCB. |

## Note

The as-built prototype schematic is the primary design evidence for this repository because it reflects the version of the board I had manufactured and tested. The integrated SIM800C schematic is included only to show my design exploration and possible future integration work.
