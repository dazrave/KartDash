# global imports
import time
import spidev

# custom imports
import RPi.GPIO as GPIO
from lib_nrf24 import NRF24

# custom scripts
import config


def radioTransmit(message):
    message = list(message)
    while len(message) < 32:
        message.append(0)

    start = time.time()
    radio.write(message)

def radioListen():
    # null