# HX711_endstop

It's a sketch for Z-probe which is based on a weight sensor and HX711 module for my Rostock 3d-printer.

This module allows auto bed leveling for any 3d-printer with any firmware.

How to use:

You'll need some stuff to assemble the sensor:

* Weight sensor like this ![sensor](https://ae01.alicdn.com/kf/HTB1wzCTKpXXXXaxaXXXq6xXFXXXU/DIYmall-Weight-Sensor-1kg-Load-Cell-Digital-Portable-Electronic-Kitchen-Scale-Weight-for-Arduino.jpg)
* HX711 ADC module
* Any arduino module (I use nano at the moment)
* Any optocoupler (I use 4n35)
* 1kOm resistor
* Some wires, solder iron, etc

First of all you need to speed up you HX711 module. By default it works on 10Hz, we need to change its speed to 80Hz.
To make this you need to connect pin *RATE* to *VCC*
![HX711 diagram](http://alpha6.ru/static/img/hx711/HX711-schema.jpg)

There are two types of modules: the one with unsoldered pad that allows high speed mode, and the other one without it.

In first case just solder the pad
![HX711 1](http://alpha6.ru/static/img/hx711/HX711-2.jpg)

In your module without this pad just unsolder pin 15 from board and connect it to VCC
![HX711 2](http://alpha6.ru/static/img/hx711/HX711-1.jpg)

Ok, now it is time to connect the sensor to module.

Simply solder wires from sensor to module in this order:

* Red -> E+
* Black -> E-
* White  -> A-
* Green -> A+

Now connect HX711 to Arduino:

* VCC -> Arduino +5V
* DT -> A2
* CLK -> A3
* GND -> Arduino GND

Enable DEBUG in sketch. Upload the sketch to Arduino and check that the weight sensor works fine over Serial monitor.

Next connect Arduino to printer board over optocoupler like it's shown on the scheme:

![scheme](http://alpha6.ru/static/img/hx711/4n35.png)

P2 is a pin from Arduino, P1 is a Z_MIN's signal pin from printers board.

Check that the sensor triggers from slightly touching the printing bed. If not, decrease the value of ```trigger``` variable.

If everything works fine, use G29 to autolevel.
