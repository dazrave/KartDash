# Introduction
A RaspberryPi and Arduino based system for managing a karting team. Designed to be easily mountable to the steering wheel.

## System
### Hardware
- [Raspberry Pi 3 Model B+ Rev 1.2](https://www.raspberrypi.org/products/raspberry-pi-3-model-b-plus/)
- 52Pi - Prototyping Pi Plate - 40 Pin Layout (_Discontinued but [similar to this](https://www.modmypi.com/raspberry-pi/prototyping-and-breakout-boards/prototyping-boards-1027/modmypi-proto-plate)_)

### Software
- [Raspbian GNU/Linux 9 (stretch)](https://www.raspberrypi.org/downloads/raspbian/)
- [Home Assistant](https://www.home-assistant.io/) (Latest)

## Devices
### Switches
- 6x Sonoff Basic flashed with [Tasmota](https://github.com/arendst/Sonoff-Tasmota)
- 4x Sonoff S20 Plugs flashed with [Tasmota](https://github.com/arendst/Sonoff-Tasmota)

### Lights
- 2x RBG LED Wifi Controllers

### Security
- 4x Hardwired PIR Sensors (GPIO)
- 1x Wireless PIR Sensor (433mhz)
- 3x Wireless IP Cams
- 4x Hardwired IP Cams
- 3x Hardwired Reed switches (GPIO)
- 1x Wireless Reed switch (433mhz)
- 1x External Siren (GPIO)

### Other
- 1x Google Home
- 3x Google Home Mini
- 2x Google Chromecast
- 1x Amazon Firestick
- 1x Nest Thermostat
- 2x Nest Protect
- 1x Sonoff Bridge (433mhz)

## Features & Automations
### Security
| Action | Type | Description |
| ------ | ------ | ------ |
| Set Alarm when away | Auto | Activates alarm when all residents are away from home at anytime |
| Turn off alarm when home | Auto | Turns off alarm when any resident arrives home at anytime |
| Set Alarm when sleeping | Auto | Activates alarm when system is satisfied all residents are sleeping |
| Turn off alarm when waking | Auto | Turns off alarm when any resident wakes up |
| Alarm reminder | Auto | Triggers reminder 'chirp' if alarm is set and **any** security sensor is activated |
| Trigger Siren | Auto | Triggers siren 30 seconds after _'Alarm Reminder'_ if alarm is still set |
| Full Lockdown | Manual | Push alerts to every resident from **any** activated security sensors (does not trigger siren) |
| Partial Lockdown | Manual | Push alerts to every resident from activated **external** security sensors (does not trigger siren) |
