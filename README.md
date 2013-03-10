inclinometer
============

Arduino sketch to calculate the angle of inclination using a 3-axis accelerometer

This is a simple example using Arduino and a 3-axis accelerometer as an inclinometer.

The accelerometer is an Analog devices ADXL345. Sparkfun has a breakout board here https://www.sparkfun.com/products/9156

It's no longer available from Sparkfun but the discussion is helpful. I borrowed the board for this video from the Gearheads
2813 Robotics Club at Prospect High School in Saratoga (http://prospectgearheads.org/).

The microcontroller is an ATmega32u4. This breakout board is available from Adafruit at http://www.adafruit.com/products/296

I installed the Leonardo bootloader on it so the project is Arduino-compatible. Any Arduino should work. The example uses the Wire library to communicate with the accelerometer and LED display using the I2C (or TWI) protocol.

As per the discussion at Sparkfun, it does seem accurate within 1 degree. To get it to work I worked through some I2C examples,
and it was pretty easy to make a little circuit that displays the result on an I2C 7-segment display I had kicking around.

Both chips connect to the microcontroller using the same clock and data wires. The only other wires on the board are for power
and ground.

The angle calculation is one line of code:

    float angle = atan2(z, y) * 180.0f / M_PI;

This will give a value between -180 and +180 degrees. I take a sample every 15 ms and average the last 10 before displaying the
result (rounded to the nearest degree).

Check here for the video http://youtu.be/wf7qeNqxBi0
