# SonyAlpine
Arduino code to interface a sony stalk with an alpine headunit.

This is tested with a sony RM-X4s and an alpine 9812, but should work with all alpine head units. To use it with other sony stalks, you may need to change the voltage values accordingly.

This is configured to use the following input circuit:

+5v 
|
|
sony stalk
|
|____________arduino pin A0
|
|
10kohm resistor
|
|
Gnd

and the following output circuit

Arduino pin d2
|
|
Alpine tip
alpine ring
|
|
Gnd


