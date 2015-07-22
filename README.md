multiwiiDataLogger
==================

*** STRIPPED DOWN FOR: ***
http://www.multiwii.com/forum/viewtopic.php?f=15&t=6570

SDCard data logger for MW based quadrocopter via the serial interface

This is the first version which already works. I did some flight recording with it and it does not affect the 
flight controller too much to drop the cycle times.

What you need to get it to work is e.g. arduino pro mini and an SPI SD card writer (http://arduino.cc/de/Reference/SD).
You just need to connect one serial from the flight controller to the serial of the arduino board (serial 0 if it has more serial ports).
The data logger will create a log directory after each start which will have a counter. So first start will log to log_0, the next start to log_1 and so on.
These folder contain the log files. For example log files see the example directory. These example files are actual recorded flight data from my quad (just the GPS data is no real flight data).

The logger will record data of the IMU, the angles (x,y and heading) and the input from the controls of your remote control. 

If you want to know more about the values please check 

http://www.multiwii.com/wiki/index.php?title=Multiwii_Serial_Protocol

