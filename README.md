# DC-64
DC-64a and DC-64d are two similar mod-kits allowing to power the Commodore-64 microcomputer with a modern switching 12V-DC power supply. Both boards feature an oscillator on board to produce the 50-60Hz Time-of-Day (TOD) clock, which would normally be extracted from the original 9V-AC power supply.

The two versions share the power supply section of the circuit and only differ in how the TOD clock is generated.
- DC-64a features a 555-like RC oscillator that can be manually calibrated with a trimmer.
- DC-64d features a high-precision crystal oscillator driving a small microcontroller that acts as a clock divider. This board does not require calibration.

If you would like to get in touch with the developer, please join the SPL discord server at this link:
https://discord.gg/gJsCgebkDw

![](https://github.com/sideprojectslab/DC-64/blob/main/doc/pictures/DC-64.png)

## Compatibility
DC-64 aims to be compatible with all versions of the C64 motherboard. A live list of verified compatible motherboards is shown below:

| Model | Assembly | Schematic | Replaced Cap | 15V connected to | 5v connected to |
|:--:   |:---:     |:---:      |:---:         |:---:          |:---:         |
|A (CR) |250407-04 |251138     | C19          |C88+           |C91+/C92      |

## Installation & Precautions
Instruction manuals on how to install and operate the board are available in PDF format alongside the fabrication data. Users shall read these instructions carefully and fully understand the circuit's limitations before installing and/or using it. Incorrect installation of the board supply or failure to comply with the recommended operating conditions may result in damage to the board and/or to the computer, with risk of overheating, fire and/or explosion.

## License
License information is included on top of all software source files as well as in all schematics. Files that do not contain explicit licensing information are subject to the licensing terms stated in the LICENSE.txt provided in the main project folder:

Unless stated otherwise in individual files, all hardware design Schematics, Bill of Materials, Gerber files and manuals are licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/4.0/

Unless otherwise stated in individual files, all software source files are Licensed under the Apache License, Version 2.0. You may obtain a copy of this license at http://www.apache.org/licenses/LICENSE-2.0

## Disclaimer
All material is provided on an 'AS IS' BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND in accordance to the license deed applicable to
each individual file.
