# QlockToo
Clone of ClockTwo using Arduino

 Setup
--------------------------------------
 Follow instructions on https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
 Follow instructions on https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/
 Follow instructions on https://randomnerdtutorials.com/esp32-wi-fi-manager-asyncwebserver/
 Install the packed libraries in /libraries folder
 Download Adafruit-Neopixel 
 Download NTPClient by Fabrice Weinberg
 Download ArduinoJson
 
 Arduino-IDE Settings
--------------------------------------
 Board: DOIT ESP32 DevKit V1
 Upload Speed: 921600
 Flash Frequency: 80 MHz
 Core Debug Level: None
 
 Code Adjustments
--------------------------------------
 Change language: 	Include "GermanDisplay.h" or "SwabianDisplay.h" in QlockToo.ino
					Declare GermanDisplay or SwabianDisplay accordingly.
 Select specials: 	Open "Specials.h" and adjust the "specials" map. 
					The server will automatically list the names in the server.
					
 How to use it
--------------------------------------
 Whenever the clock has no wifi credentials it will open a "QlockToo" network. Enter "QlockToo" as password. (defaults)
 After connecting it will synchronize automatically via NTP.
 In your home-network you can should be able to connect your QlockToo by "http://qlocktoo" or "http://qlocktoo.fritz.box" 
