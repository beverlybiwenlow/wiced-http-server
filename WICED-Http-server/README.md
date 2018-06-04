Configuring Wifi using web server
=================================

This program aims to register wifi credentials for new users using a mobile hotspot.


Logic of the program:
- Program will connect to a hotspot, which will then start a webserver and load a webpage that takes in a wifi login and password
- Upon submission on the webpage, these wifi credentials will be stored and the WICED wifi module will connect to it instead of the hotspot
- Loop will run 3 times:
	- In the first loop, program checks to see if wifi module is connected to anything. This will fail since it is not connected yet. The program then connects the wifi module to the mobile hotspot.
	- In the second loop, program checks connectivity again. This time, wifi module is connected to mobile hotspot. Program then starts a webserver. Using the mobile device, go to the static IP set and fill in the form with intended wifi credentials. Submit. Wifi module should then connect to the new wifi.

	
Steps to be taken:
1. Edit WLAN_SSID_2 and WLAN_PASS_2 to reflect the SSID and password of the mobile hotspot to be used.
2. Edit staticIP to reflect the static IP address for the webpage. (Note: for mobile hotspots, start with 192.168.43.__)
3. Run the program
4. When the serial monitor shows that hotspot is connected and server is set up, go to a browser and enter the static IP address
5. Enter the SSID and password of the wifi to be registered onto the webpage and click submit
6. Serial monitor will show that new wifi has been connected to