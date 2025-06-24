# Circuit Setup

![Circuit Diagram](https://github.com/user-attachments/assets/7f04088d-004e-413f-bb50-87c71d4f9813)


**Microprocessor used:** Arduino UNO R3

**List of other sensors:**

1) **MQ135 Gas sensor -** General air quality idea
2) **DHT11 sensor -** Temperature and Humidity
3) **SSD1306 OLED display -** OLED display 

**NOTE:** When working with the oled display, I had the problem of getting garbage pixels in bottom right of the screen, alternating between the frames. It was related to the problem that Strings are usually stored in SRAM of arduino, and in order to store it in flash memory, we have to use F() constructor. 

Thread of user with similar problem: [https://forum.arduino.cc/t/ssd1306-oled-trash-pixels/1209515](https://forum.arduino.cc/t/ssd1306-oled-trash-pixels/1209515)

For more information: [https://docs.arduino.cc/learn/programming/memory-guide/#sram-memory-optimization](https://docs.arduino.cc/learn/programming/memory-guide/#sram-memory-optimization)
