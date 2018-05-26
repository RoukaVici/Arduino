# Roukarduino
The code running on the RoukaVici gloves themselves.

# Installation
Connect to the Arduino & upload the sketch.
**If the bluetooth card is mounted on the serial ports (as it should be), remember to unplug it before uploading.**

# Configuration
Two main variables are defined:
- `motors`: The number of motors connected to a single arduino
- `tab[motors]`: The physical pin values of each motor. Each motor in the tab will be called by its number (the first motor being motor #0, etc)

These numbers can change between releases.

# How it Works
## Reading data
The Arduino reads off its Serial port (which usually will be connected to a Bluetooth card). When a `serialEvent` is fired, the Arduino checks for incoming data, and if there are two available bytes, it reads them and sends the vibration order to the proper motor.

Messages are currently structured as such:
- First byte is the motor number, by index in the `tab` variable: `0-255`
- Second byte is intensity, from off to on: `0-255`

## Errors
The Arduino signifies that it encountered an error with three short vibrations. The code is in the `error()` function.
