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

To turn the antenna to a certain azimuth, find out the ESP32's IP address and 
run this `curl` command:

```
$ curl http://192.168.1.144/turn?params=350
```

Schematics will be added later.

Alexa interface will be added later.
