Configuring Wifi using web server
=================================

This program aims to register wifi credentials for new users using a mobile hotspot.

Logic of the program:
- Program will connect to a hotspot, which will then start a webserver with a webpage that takes in a wifi login and password
- Upon submission on the webpage, these wifi credentials will be stored and the WICED wifi module will connect to it instead of the hotspot
- Loop will run 3 times:
	- In the first loop, program checks to see if wifi module is connected to anything. This will fail since it is not connected yet. The program then connects the wifi module to the mobile hotspot.
	- In the second loop, program checks connectivity again. This time, wifi module is connected to mobile hotspot. Program then starts a webserver and shows the IP address of the webpage. Using the mobile device, go to the webpage and fill in the form with intended wifi credentials. Submit. Wifi module should then connect to the new wifi.
	- In the third loop, program checks connectivity once more. This time, wifi module should not be connected to the hotspot anymore but to the new wifi. 


Issues yet to be solved:
- Wifi module seems to be unable to connect to dual services (hotspot and new wifi).
- Wifi module also seems to be unable to disconnect from the first (hotspot) and connect to the second (new wifi)
- Have yet to set the webpage to open on a static IP address