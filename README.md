# GD32V Driver Suite
C device drivers for the GigaDevice GD32VF103 microcontroller built on the
official firmware SDK. Supports various devices like stepper motors,
displays and sensors. It comes with several demo firmwares. The recommended
development board for these firmwares is the Sipeed Longan Nano. However,
since said board was permanently discontinued since January 2023, you might 
need to get a different development board and adjust the configuration to
your needs.


# Project goals
The goal of this project is to provide an easy to use interface for
intermediate C programmers to work with using this RISC-V microcontroller
unit together with mostly inexpensive devices that can be bought easily or
scavenged from recycled electronics

# The device drivers
My device drivers are designed to be used standalone on top of the MCU SDK
and they are not tied to any RTOS or third party platform. You could even
untie them from the GigaDevice SDK and directly manipulate the MCU register
addresses if you wanted to completely divorce your firmware from it.
The official GigaDevice SDK is extremely similar to libopencm3 so you can
easily port the drivers over to it by performing some renames.

# Currently supported devices
Displays:
* HD44780-like character LCD modules

Stepper motors:
* 28BYJ-48

# How to use?
Each device driver comes with an accompanying .txt file explaining how to
configure it to your needs. On your firmware project you will need a
config.h header file to put all your configurations into.