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
- **Connections**:
  - VCC	: 5V
  - GND : GND
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

### Config.h

Create a config.h in the root of the source directory. This file is not source controlled, and listed in .gitignore
The purpose of config.h is to store common variables that may be sensitive to check in to git. 

The mandatory config.h contents are:

```cpp
// config.h
#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials
#define WIFI_SSID "your wifi ssd"
#define WIFI_PASSWORD "j00r passwird"

// Custom NTP servers. Optional. See README.md!!!
#define NTP_SERVER1 "0.za.pool.ntp.org"   // defaults for my ZA pool
#define NTP_SERVER2 "1.za.pool.ntp.org"

#endif
```

#### NTP

NTP stands for Network Time Protocol. It's a networking protocol for clock synchronization between computer systems over packet-switched, variable-latency data networks. NTP is crucial for maintaining accurate time across devices connected to the internet.

In the context of *MecGrowMancer*:
- NTP is used to synchronize the device's RTC (Real-Time Clock) with global time servers.
- This ensures that your device maintains accurate time, which is essential for timestamping data, scheduling tasks, and other time-dependent operations.
- The device connects to NTP servers once a day to check and correct any time drift.

The config example above uses local ZA (South Africa) pools, but you should find the appropriate ones for your region at https://www.ntppool.org/en/

How it works:
1. The device connects to the specified NTP servers.
2. It requests the current time from these servers.
3. The received time is then used to update the device's RTC.
4. This process compensates for any drift in the RTC, ensuring long-term time accuracy.

Choosing NTP Servers:
- For personal or small-scale projects, using regional NTP pool servers is appropriate.
- For larger deployments or commercial products, consider setting up your own NTP servers or using commercial NTP services.

**Important**
For distributed/vendor use, see https://www.ntppool.org/vendors.html
Never hardcode public pool hostnames into commercial/distributed/vendor systems. This can lead to overloading public NTP servers and is against best practices.

Customizing NTP Servers:
- If `NTP_SERVER1` and `NTP_SERVER2` are defined in `config.h`, the device will use these custom servers.
- If not defined, it will fall back to default servers ("pool.ntp.org" and "time.nist.gov").
- Using geographically closer NTP servers can improve synchronization accuracy and reduce network latency.

Remember, accurate time is crucial for many IoT and data logging applications, making NTP an essential feature of the MecGrowMancer system.

## Setup and Installation

This will be documented in due time [after prototyping]

## Usage

TODO

## Contributing

TODO

## License

Make sure that a LICENSE or COPYING file accompanies this code =)
MecGrowMancer - ESP32-based Homestead/Farm/Garden/Home/Garage Manager
Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
License: GNU GPLv3 (see LICENSE/COPYING file for details)

## Contact

Marlon van der Linde <marlonv@pm.me>
