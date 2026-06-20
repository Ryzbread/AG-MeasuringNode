**Measuring Node Overview**

The Measuring Node is a critical component of the Garden Automation System, responsible for monitoring and reporting soil moisture levels to the Main Controller. Each Measuring Node consists of an ESP-01S WiFi module, soil moisture sensor, and a solar panel.

___

**Measuring Node Components**

1. **WiFi Module (ESP01S)**: Enables communication between the Measuring Node and Main Controller via WiFi.
2. **Soil Moisture Sensor**: Measures soil moisture levels to determine watering needs.
3. **Solar Panel with Charge Controller**: Supplies intermittent power to the ESP and sensor.

**Measuring Node Functionality**

1. **Communication with Main Controller**: The Measuring Node communicates with the Main Controller using WiFi to send soil moisture readings.
2. **Soil Moisture Measurement**: The Measuring Node measures soil moisture levels using the integrated soil moisture sensor.
3. **Data Transmission**: The Measuring Node transmits soil moisture data to the Main Controller for analysis and control decisions.

**Notes**

* Each Measuring Node is dedicated to a specific watering zone, allowing for precise monitoring and control of each area.

___

**Dependencies**
* Arduino-Cli or Arduino IDE (Programming)
* Additional boards manager URLs
    > http://arduino.esp8266.com/stable/package_esp8266com_index.json
* WiFiManager
    > arduino-cli lib install WiFiManager
* Serial Programming Interface (FTDI serial converter)

___

**Programming**

1. Pinout
    * FTDI --> ESP-01S
    * Vcc --> 3v3
    * GND --> GND
    * Tx --> Rx
    * Rx --> Tx
    * Vcc --> RST
    * Gnd --> IO0
2. Connect FTDI to computer via USB
3. Board Config: Generic ESP8266 Module
4. Port: FTDI serial converter
5. Upload via Arduino-Cli or Arduino IDE

___

**First Time Setup**
1. Pinout
    * FTDI --> ESP-01S
    * Vcc --> 3v3
    * GND --> GND
    * Tx --> Rx (Optional)
    * Rx --> Tx (Optional)
2. Connect FTDI to computer via USB
3. Connect Smart Phone to AP WiFi Network "BootstrapNetwork"
4. Enter "NetworkPassword" for the password
5. Follow Initial Sign-On instructions to configure Wifi Network
6. Disconnect and reconnect power
7. Ensure node connects to configured Network

