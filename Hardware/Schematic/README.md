# Schematic

This folder contains schematic evidence for the Emergency Exit Light Health Checker hardware.

The main schematic included here represents the as-built prototype version of the board, where the cellular modem was implemented using a plug-in SIM800L module. This matches the assembled prototype PCB and retrofit installation images shown elsewhere in the repository.

A later/alternative schematic variant explored integrating the SIM800C modem, SIM card holder and ESD protection directly onto the PCB. That version is included separately as a design variant and is not the same as the manufactured prototype shown in the project images.

## Included Files

| File | Description |
|---|---|
| `Schematic_ESP32_AC_SIM800L_AsBuilt_Prototype.pdf` | As-built prototype schematic using ESP32, plug-in SIM800L module, BH1750 light sensor, relay switching and the required power sections. |
| `Design_Variants/Schematic_ESP32_SIM800C_OnPCB_Concept.pdf` | Alternative concept/design variant with SIM800C, SIM card holder and ESD protection integrated directly onto the PCB. |

## Note

The as-built prototype schematic is the primary design evidence for this repository. The integrated SIM800C schematic is included only to show design exploration and future integration work.
