# MecGrowMancer

MecGrowMancer is an ESP32-based device designed for farm, homestead, and garden applications.
It utilizes (a growing list of) sensors to monitor environmental conditions and provide useful data for plant growth and management.
The project codename MecGrowMancer is derived from the words 'mechanical' (devices, machines, real world things),'grow' (growing, nurturing, nature) and 'mancer' (to control things magically, which hacking at this codebase sometimes is).

## Development Philosophy

The MecGrowMancer project is built on principles of efficiency and optimization, tailored for resource-constrained microcontroller environments:

1. **Language**: Primarily C/C++, leveraging low-level control and efficiency.
2. **Memory Management**: Careful allocation and deallocation to minimize RAM usage.
3. **CPU Utilization**: Task scheduling and cooperative multitasking for balanced processing.
4. **Power Efficiency**: Strategic use of sleep modes and sensor polling intervals.
5. **Code Modularity**: Structured for maintainability and minimal coupling between components.
6. **I/O Optimization**: Efficient use of hardware interfaces and communication protocols.
7. **Compiler Optimizations**: Utilizing appropriate flags for size and speed trade-offs.
8. **Resource-Aware Algorithms**: Implementing algorithms suited for limited computational resources.
9. **Cost-Effective Hardware**: Selecting components that balance functionality and affordability.
10. **Real-Time Responsiveness**: Ensuring timely execution of critical tasks.

These strategies aim to create a system that is fast, power-friendly, and economical, while maintaining reliability and functionality.

## Hardware Components

### ESP32 DOIT DevKit

The core of the MecGrowMancer system is built around the ESP32 DOIT DevKit, providing Wi-Fi and Bluetooth connectivity along with powerful processing capabilities.

### LCD Display

1602 in I2C mode:

VCC	: 5V
GND : GND
SDA : GPIO 21
SCL : GPIO 22

- **Model**: 16x2 LCD (1602) in I2C mode at hardware address 0x27
- **Connections**:
  - VCC : 5v bus
  - GND : GND bus
  - SDA : GPIO 21
  - SCL : GPIO 22

### BMP280 Temperature and Pressure Sensor

- **Model**: DFROBOT / Bosch based BMP280 Barometric and Temperature sensor at hardware address 0x77
- **Connections**:
  - VCC : 3.3V
  - GND : GND
  - SDA : GPIO 21
  - SCL : GPIO 22

## Features
This list will change (mostly expand) as the project develops.

- Real-time ambient temperature and pressure monitoring
- Clear LCD display/dashboard for intuitive data representation
- Efficient power management

## Software

The MecGrowMancer firmware is developed using the Arduino IDE with ESP32 support. Key features include:

- Modular code structure for maintainability and learnability (for new developers)
- Sensor data processing and display
- Debug output via serial communication

## Setup and Installation

This will be documented in due time [after prototyping]

## Usage

TODO

## Contributing

TODO

## License

INFO PENDING

## Contact

Marlon van der Linde <marlonv@pm.me>
