# Denon AVR 3805 Control via Web Interface

This project allows you to control your Denon AVR 3805 receiver over a web interface. You can turn the receiver on or off, adjust the volume, mute or unmute, and more, all from a web browser.

## Features

- Power On/Off
- Volume Control (Up/Down)
- Mute/Unmute
- Set Volume Level
- Tune to Radio Stations

## Interface Documentation

For detailed information about the RS-232 commands used to control the Denon AVR 3805, refer to the [Denon AVR 3805 RS-232 Command Reference](https://assets.denon.com/documentmaster/uk/139_avr-3805_rs232.pdf).

## TODO

The following commands are missing and need to be implemented in the library:

- **Input Selection:** Add commands to select different input sources (e.g., DVD, TV, etc.).
- **Surround Modes:** Implement commands to set various surround modes (e.g., Dolby, DTS, Stereo).
- **Zone Control:** Add commands to control additional zones (e.g., Zone 2, Zone 3).
- **Speaker Configuration:** Add commands to configure speaker setup and settings.
- **Home Assistant Integration** Provide mediaplayer yaml for homeassistant so that it can be used with homeassistant / homekit -> Siri
