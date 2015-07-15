# SonyAlpine
Arduino code to interface a sony stalk with an alpine headunit and provide USB Keyboard functionality. Switchable between fully operating the headunit and emulating a usb keyboard, while still controlling volume and source on the headunit. Switch using the bottom (unlabled) button on the sony stalk, when in HU mode, the L led on the arduino will light, when in USB mode it will go out. Currently the disc change functionality (shift function) does not change disc, just skips track, but still skips track when in keyboard mode. 

USB keyboard functionality is only available on arduinos which support it, such as the Leondardo, but the headunit functionality will (should) work on any arduino, tested on Leonard and Uno.

This is tested with a Sony RM-X4s stalk with the following alpine headunits:  CDA-9812, INA-333, CDE-9881, UTE-72, but should work with all alpine head units. Tested and does not appear to work with IVA-D310. To use it with other sony stalks, you may need to change the voltage values accordingly.


Eagle and PDF schematics included.

