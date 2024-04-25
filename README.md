# Automatic Plant Watering System

This project is an automated plant watering system designed to ensure your plants receive the right amount of water each day without manual intervention. It includes 3D printable designs for any required parts, as well as the Arduino code needed to control the system.

## Features

- **Daily Watering:** Configured to pump water to your plants once a day.
- **Time Set Feature:** A start switch allows you to set the time of day for watering.
- **3D Printable Components:** STL files for all the 3D printable parts of the system.
- **Arduino-Controlled:** Utilizes an Arduino Nano for managing the watering process.

## Hardware Requirements

- Arduino Nano
- Relay Module
- [12V DC Motor Pump](http://surl.li/syvim) (29mm diameter and 80mm length) 
- Switches for setting up the start time

## STL Designs

The `stl` directory contains all the necessary 3D models that you can print to build the physical structure of the watering system. Ensure that you use a suitable material for water exposure.

## Code

The `code` directory holds the Arduino sketch that you need to upload to the Arduino Nano. This code manages the relay and pump operation, turning the pump on once a day at the specified time.

## Setup

1. Assemble the 3D printed parts according to the design files.
2. Connect the Arduino Nano to the relay module and the pump.
3. Attach the switches to the system to set the watering time.
4. Upload the provided Arduino code to the Arduino Nano.
5. Set the system near your plants with the pump submerged in the water reservoir.
6. Use the switch to set the start time for watering.

## Contributions

We welcome contributions to this project! If you have suggestions or improvements, please fork this repository, create a feature branch, and submit a pull request. Keep in mind the code can be improved. 


## Disclaimer

This project involves electrical components and water. Exercise caution and ensure all electrical connections are secure and waterproof. The creators of this project are not liable for any damage or accidents stemming from the use of this system.


## Images

<img src="https://utfs.io/f/2f54125d-0678-4611-bb29-98994bed787b-ujtylh.JPG" width="600" height="330">
<img src="https://utfs.io/f/a5e272b5-0f60-4421-b773-ed5e36ec6f2c-ujtylg.JPG" width="600" height="330">
