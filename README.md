# DIY Hexapod Robot

A six-legged walking robot controlled over Bluetooth. The project includes Arduino firmware and 3D-printable parts.

## Features

- **Inverse kinematics** – per-leg IK solver for coxa, femur, and tibia joints
- **Tripod gait** – alternating two groups of three legs for smooth walking
- **Bluetooth control** – joystick input via the [Dabble](https://thestempedia.com/product/dabble/) mobile app
- **3D-printable body & legs** – STL files included for all structural parts

## Hardware

| Component | Details |
|---|---|
| Microcontroller | Arduino (any board with I²C and a serial UART) |
| Servo drivers | 2 × PCA9685 16-channel PWM boards |
| Servos | 18 × standard hobby servos (3 per leg) |
| Bluetooth module | HC-05 / HC-06 (or equivalent, connected to pins 2 & 3) |
| Leg geometry | Femur 90 mm · Tibia 160 mm |

## Repository Layout

```
firmware/
  include/   # Header files (config, kinematics, gait, utils)
  src/       # Source files (main, kinematics, gait, config, utils, test_bluetooth)
models/
  body/      # STL files for the upper and lower body sections
  leg/       # STL files for coxa, femur, tibia bones and servo attachment
diy-documentation.pdf   # Full build guide
```

## Getting Started

### Prerequisites

Install the following Arduino libraries via the Library Manager:

- [Adafruit PWM Servo Driver](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library)
- [Dabble](https://thestempedia.com/docs/dabble/)

### Building & Uploading

1. Open the `firmware/` folder in the [Arduino IDE](https://www.arduino.cc/en/software) (or PlatformIO).
2. Select your board and port.
3. Click **Upload**.

### Control

Pair your phone with the Bluetooth module, open the **Dabble** app, and use the **GamePad** module. The left joystick controls walking direction.

## 3D Printing

Print the STL files from `models/body/` and `models/leg/`. Refer to `diy-documentation.pdf` for assembly instructions and recommended print settings.

## License

This project is provided as-is for personal and educational use.
