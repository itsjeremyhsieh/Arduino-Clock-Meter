# Arduino-timer-meter
This project is a digital clock and environmental meter using an Arduino board and a 16x2 LCD display. The system displays the current time, humidity, and temperature in Celsius on the display.

# Requirements
* Arduino Uno R3
* DS1302
* LCD 1602 display
* DHT11 temperature and humidity sensor
* Breadboard
* Jumper wires

## Installation
Download the code from the GitHub repository.
Connect the components as follows:

![clock_meter](https://user-images.githubusercontent.com/94349736/233422847-9f5b093f-94cc-44a5-b1e0-904c94519a58.png)

Upload the code to your Arduino board using the Arduino IDE.

* Note that due to the power supply limitation of Arduino, the DHT11 must be comnnected to the 3.3V output, the LCD display and the DS1302 must be connected to the 5V output.
## Usage
Power on the system and wait for the LCD display to initialize.

The display will show the current time, as well as the temperature and humidity readings from the DHT11 sensor.

The system will automatically update the time and sensor readings every 10 seconds.

## Acknowledgments
This project was inspired by the need for a simple, yet effective way to display the time and environmental readings in a compact and easy-to-read format.
