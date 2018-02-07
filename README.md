"# ESP8266-in-Arduino-with-WPA2-Enterprise" 

How to Install the ESP8266 Board in Arduino IDE from GitHub
with WPA2 Enterprise WiFi Support [Windows version]

1. Download and install Git for Windows by 
   - open web browser and goto https://git-scm.com/download/win

2. Download and install Python 2.7 by
   - open web browser and goto https://www.python.org/downloads/

3. open Git CMD as Administrator by
   - click Start / Git
   - right click Git CMD
   - select More / Run as administrator

4. in Git CMD type
   
   cd "C:\Program Files (x86)\Arduino"

   (64bit Windows)
   
   or

   cd "C:\Program Files\Arduino"
   
   (32bit Window) 

   (or change to your Arduino IDE install folder)

5. in Git CMD type

      cd hardware

6. in Git CMD type

      mkdir esp8266com

7. in Git CMD type

      cd esp8266com

8. in Git CMD type

      git clone https://github.com/esp8266/Arduino.git esp8266

9. in Git CMD type

      cd esp8266/tools

10. in Git CMD type

      c:\python27\python get.py
      
      (in case you install python in "c:\python27" folder)

11. Restart Arduino
