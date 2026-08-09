# Smart Glove Mouse

An ESP32-based wearable human-computer interaction system that
converts hand gestures and wrist movements into wireless mouse
operations.

## Project Overview

The Smart Glove Mouse is a wearable gesture-controlled interface
developed using an ESP32, MPU6050 IMU, and flex sensors.

The system detects finger bending using flex sensors and wrist
movement using the MPU6050 gyroscope. The ESP32 processes the
sensor data and communicates with a computer through Bluetooth,
allowing the user to perform mouse operations without a
conventional physical mouse.

## Features

- Wireless Bluetooth mouse control
- Hand gesture-based cursor control
- Left-click and drag operation
- Right-click operation
- Scroll control using thumb gesture and wrist movement
- MPU6050-based motion sensing
- Flex sensor-based finger detection
- Sensor data smoothing for improved stability

## Hardware Components

- ESP32
- MPU6050
- 3 Flex Sensors
- Connecting wires
- Power supply

## Pin Configuration

| Sensor | ESP32 Pin | Function |
|---|---:|---|
| Thumb Flex Sensor | GPIO 34 | Scroll control |
| Index Flex Sensor | GPIO 35 | Left click & drag |
| Middle Flex Sensor | GPIO 32 | Right click |

## Software and Libraries

- Arduino IDE
- Embedded C/C++
- ESP32 Bluetooth
- `BleMouse` Library
- `Adafruit MPU6050` Library
- `Adafruit Sensor` Library
- `Wire` Library

## Working Principle

The flex sensors detect finger bending and provide analog
signals to the ESP32.

The MPU6050 measures wrist movement using its gyroscope.
The ESP32 processes the sensor readings and applies smoothing
to reduce unwanted cursor movement.

The processed gestures are converted into mouse commands
and transmitted wirelessly to a paired computer using
Bluetooth.

## Gesture Mapping

| Gesture / Movement | Mouse Function |
|---|---|
| Index finger bend | Left click |
| Index finger held bent | Drag |
| Middle finger bend | Right click |
| Thumb straight | Normal cursor movement |
| Thumb bent + wrist tilt upward | Scroll up |
| Thumb bent + wrist tilt downward | Scroll down |

## Code

The main Arduino source code is available in:

`smart_glove_mouse.ino`

## Applications

- Human-computer interaction
- Gesture-controlled interfaces
- Wearable electronics
- Assistive technology
- Hands-free computer interaction

## Future Scope

- Addition of more gestures
- Improved gesture classification
- Machine-learning-based gesture recognition
- Reduced power consumption
- Integration with additional wearable sensors
- Improved wireless control

## Author

**Sreelakshmi K S**

B.Tech Electronics and Communication Engineering  
Rajiv Gandhi Institute of Technology, Kottayam
