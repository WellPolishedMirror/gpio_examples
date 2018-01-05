# Fedora GPIO examples

This repository contains a series of examples on how to manipulate 
the GPIOs on the raspberry pi 3 when running Fedora.

The GPIOs are exposed as a character device; ioctl calls are used
to get a set of pins and to turn them on/off.

In the Linux kernel, the gpio pins are defined in the device tree file:
arch/arm/boot/dts/bcm283x.dtsi

The driver that creates the character device is located:
drivers/pinctrl/bcm/pinctrl-bcm2835.c

The userspace ioctls and structures are defined here:
/usr/include/linux/gpio.h

Examples:
- chipinfo     : Displays information about the GPIO Chip. 
- lsgpio       : Shows all GPIOs and their current uses.
- blink        : Switches three LEDs on/off 
- button_poll  : Infinitley checks buttons and sleeps.
- button_event : Blocks until button has been pressed.

These examples are written in C, and are compiled by running make.

For a python library to manipulate GPIOs on Fedora Arm, check out:
https://github.com/bookwar/python-gpiodev

[Raspberry Pi 3 pinout from http://pinout.xyz]
          +---+---+
3v3 Power | * | * | 5v Power
BCM 2     | * | * | 5v Power
BCM 3     | * | * | Ground  
BCM 4     | * | * | BCM 14  
Ground    | * | * | BCM 15  
BCM 17    | * | * | BCM 18  
BCM 27    | * | * | Ground  
BCM 22    | * | * | BCM 23  
3v3 Power | * | * | BCM 24  
BCM 10    | * | * | Ground  
BCM 9     | * | * | BCM 25  
BCM 11    | * | * | BCM 8   
Ground    | * | * | BCM 7   
BCM 0     | * | * | BCM 1   
BCM 5     | * | * | Ground  
BCM 6     | * | * | BCM 12  
BCM 13    | * | * | Ground  
BCM 19    | * | * | BCM 16  
BCM 26    | * | * | BCM 20  
Ground    | * | * | BCM 21  
          +---+---+
