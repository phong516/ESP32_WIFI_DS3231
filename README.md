# ESP32_WIFI_DS3231

* These Arduino Sketches contain 2 main parts: WiFi and RTC DS3231 *

1. WiFi
- Connect to a WiFi network.
- Scan the available WiFi networks.
- When there is no network connected, ESP32 broadcast a softAP network. When the user connect to this WiFi, a captive portal will automatically open, allows user to manually enter the WiFi's credential or choose an available WiFi to connect. 

2. RTC DS3231
- Collect RTC data.
- Adjust the time.

* Neccessary knowledge *
- WiFi network.
- DS3231 datasheet.
- I2C protocol for DS3231.
- html, css, js for webserver setups and configurations.