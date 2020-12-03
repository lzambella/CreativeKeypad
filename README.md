Creative Keypad
======

Senior Project 2020-2021

Macropad with additional controls.

## Introduction
This is the firmware for a device that acts as an HID keyboard with additional
options. The device contains 12 input keys and 6 rotational keys (12 additional
inputs) for a total of 24 configurable actions. The device itself uses an AVR
microcontroller. 

## Pinout
The device contains 3 rows and 6 columns (2 columns are reserved for the
encoders built in push buttons that are not implemented as of yet) for the
switches.

        C1  C2  C3  C4  C5  C6
    R1  NA  0   1   2   3   NA
    R2  NA  4   5   6   7   NA
    R3  NA  8   9   A   B   NA

        PIN
    R1  B0
    R2  B1
    R3  B2

    C1  B3
    C2  B7 
    C3  D0
    C4  D1
    C5  D2
    C6  D3

Each key can be programmed to a single keystroke currently, future updates will
allow for multiple keystroke actions.

The encoders each have two actions each for both clockwise and counter clockwise
rotation. These can be configured as well. Each encoder utilizes two GPIO pins
as well.



Uses TMK as the core ( https://github.com/tmk )
