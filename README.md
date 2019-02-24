# Antenna Rotator with Voice Interface (model)

This project started as a simple demo of Amazon Alexa capabilities.
First I implemented it in Python on Raspberry Pi.
Here is the [video](https://www.youtube.com/watch?v=EuMAzldERhc).

I received a lot of positive feedback on that small weekend project.
Most popular request was to add a compass capability to be able not just to tell the antenna
to turn "90 degrees" or "minus 100 degrees", but to set the azimuth: "turn TO 45 degrees",
which is North-North-East.
Another request was to be able to say the country, like "turn to Nigeria" and the application
should be able to find the heading to Nigeria in the database and turn the antenna.

Now I'm migrating this application to ESP32 (mostly because it's so much fun 
working with this small but powerful microcontroller). Now it is implemented 
as REST API interface.

## Components

For this project I used a *ESP32-PICO-KIT* board. 
Documentation from Espressif can be found [here](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/get-started-pico-kit.html).
The board itself is available on [Amazon](https://www.amazon.com/gp/product/B07BTBGCFP/) for $19.99 for a 2-pack.

I used a cheap stepper motor *28BYJ-48* which is also available on [Amazon](https://www.amazon.com/ELEGOO-28BYJ-48-ULN2003-Stepper-Arduino/dp/B01CP18J4A/). 
This library was very helpful and easy to use: https://github.com/tyhenry/CheapStepper

I used an accelerometer/magnetometer sensor module *GY-511* (similar to LSM303) which is available on [Amazon](https://www.amazon.com/TOOGOO-LSM303DLHC-Compass-Acceleration-Arduino/dp/B075FPBLSD/).


## Connections

### ESP32 to Stepper Motor

* GPIO12 -> IN1
* GPIO13 -> IN2
* GPIO14 -> IN3
* GPIO15 -> IN4

Don't forget to connect an external power source (5 -12V) to the motor controller board.

### ESP32 to Compass Module

* GPIO21 -> SDA
* GPIO22 -> SCL
* 3.3V -> 3.3V
* GND -> GND

## REST API

To turn the antenna to a certain azimuth, find out the ESP32's IP address and 
run this `curl` command:

```
$ curl http://192.168.1.144/turn?params=350
```

Alexa interface will be added later.

## NOTES

Originally I used a piece of wire to emulate the antenna. 
I connected it to the motor's shaft and bent as Inverted-L.
This way it was easy to track its movement.
I tested the compass module separately and everything was fine: it showed me direction perfectly fine.
But when I tied it to the "antenna" it stopped working.
It was showing always the same value around 270 with small fluctuations, regardless of its orientation.
After quick analysis I had that "a-ha!" moment: the wire I used was made of steel and obviously it affected the compass.
Changing the wire to a copper one fixed the problem.
