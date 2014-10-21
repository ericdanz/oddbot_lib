oddbot_lib
==========

A library of functions applicable to the oddbot and its modules

Serial
============
Called via 
CSerial serial("portname",baudRate)
baudRate is an integer (e.g. 9600, 38400)
portname is a string (e.g. "/dev/ttyACM0")

The functions are 
serial.ReadData();
returns an integer that you can use for error checking (if it is -1 that is bad)

serial.SendData("string to send")
sends that data, returns an integer you can use for error checking


for the future - change the way errors are handled. Sometimes they still cout. 


Get Subnet
==============
No clue, ask Chris
