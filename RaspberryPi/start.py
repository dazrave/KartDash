# global imports
import time
import spidev

# custom imports
import RPi.GPIO as GPIO
from lib_nrf24 import NRF24

# custom scripts
import config
import functions

#from config import mainPath, moviePath, showPath, filePath, recyclePath, rgUser, rgPass, fileBot
#config = [mainPath, moviePath, showPath, filePath, recyclePath, rgUser, rgPass, fileBot]


# prepare gpio usage
GPIO.cleanup()
GPIO.setmode(GPIO.BCM)

# setup radio
pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1], [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]
radio = NRF24(GPIO, spidev.SpiDev()) 
radio.begin(0, 17)
radio.setPayloadSize(32)

#radio.setChannel(0x75) # Alpha
radio.setChannel(0x76) # Bravo

radio.setDataRate(NRF24.BR_1MBPS)
radio.setPALevel (NRF24.PA_MAX)
radio.setAutoAck(True)
radio.enableDynamicPayloads()
radio.enableAckPayload()