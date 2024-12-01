# Alchemorium

Alchemorium is an ESP32-based device that functions as a research and monitoring station. It integrates various sensors, from low-end to custom-built, to collect and analyze environmental data. Alchemorium enables farms, homesteads, etc to track, study, and understand their environments, offering insights into ambient, climate, weather or natural patterns. This modular system is designed to be simple, efficient, and robust, serving as a data logger, early alert system, personal weather station, or research tool.

![GNU GPLv3 Logo](https://www.gnu.org/graphics/gplv3-with-text-136x68.png)

## Development Philosophy

Note: While this repository transitions from MecGrowMancer to Alchemorium, old references may be present.

The Alchemorium project is built on principles of efficiency and optimization, tailored for resource-constrained microcontroller environments:

1. **Language**: Primarily C/C++, leveraging low-level control and efficiency.
2. **Memory Management**: Careful alloc/dealloc to minimize RAM usage.
3. **CPU Utilization**: Task scheduling and cooperative multitasking for balanced processing.
4. **Power Efficiency**: Strategic use of sleep modes and sensor polling intervals.
5. **Code Modularity**: Structured for maintainability and minimal coupling between components.
6. **I/O Optimization**: Efficient use of hardware interfaces and communication protocols.
7. **Compiler Optimizations**: Utilizing appropriate flags for size and speed trade-offs.
8. **Resource-Aware Algorithms**: Implementing algorithms suited for limited computational resources.
9. **Real-Time Responsiveness**: Ensuring timely execution of critical tasks.
10. **New Arduino/ESP developer friendly**: Readable and welcoming to all levels of the community (with hope)

These strategies aim to create a system that is fast, power-friendly, and economical, while maintaining reliability and functionality. Whether any of them stand strong, remains to be seen.

## Adding and Expanding your own features

Alchemorium already consists of the core functionality needed to operate on its own. There are already LCD interfacing, Wifi connectivity, Time synchronisation, various sensors for environmental input, etc. The task scheduler is ready for use, but adding tasks (like sensor measurements, updates, etc) to the scheduler. Adding your own features should be simple, and with luck, done by copying the 
current setup (or, mimicking it).

- INIT: Alchemorium.cpp is the main file, and contains the usual setup() function, where you will add your new sensor/feature initialisation calls
- SCHEDULER: The task scheduler is located in Alchemorium.cpp, and adding a task can be seen in current working examples in the file (section 'SCHEDULER TASKS')
- Create modular code for your new feature, by adding a descriptively named source and header file. If you are adding a rocket launcher, you'll add rocket_launcher.cpp and rocket_launcher.h
- Write the code you need, and put any 'common configuration' constants in config.h. Leave complicated, technical constants in your .h
- If the feature requires lcd display, you can call current (or add new) useful LCD functionality (see lcd_display.h)
- If the feature requires display/input on the web dashboard, then edit /data/index.html (and upload to flash). See websrv.h
- Test, follow philosophy, write modular, efficient, non-blocking code.

### File reference

These are the source file names (.cpp and .h) and their intended purposes

- Alchemorium : Main file with setup()+initialisers, task scheduler, main loop
- bmp280_sensor : The sensor control for the Bosch BMP280 Temperature and Pressure sensor
- config : Configuration constants for commonly tuned parameters only
- lcd_custom_chars : Custom characters live here
- lcd_display : Some convenient and needed code for working the the 16x2 i2c LCD
- ldr_ambient : Control/Measurements of ambient light levels from simple analog LDR sensor modules
- rtc_module : Realtime Clock module code. NTP sync'd
- scheduler : The task scheduler (non blocking, timed calling of other code)
- sensor_data : The structure that houses the last updated sensor input values, used by things like the LCD and Web Dashboard
- serial_debug : Serial print line code to make debug a bit easier/uniform to read on the serial console
- websrv : Web server and dashboard loading. Runs only if wifi is connected
- wifi_manager : simple wifi connection, retry, etc code

## Features
Features are developed and added as time/weather/resources and components available allows. Project sponsoship can be translated to expedition. =)

### Completed
- **Interface**: LCD (16-character/2-line)
- **Interface**: Web UI
- **Network**: Wireless network connectivity
- **Time**: Real-time clock backed
- **Time**: NTP (Network Time Protocol) synchronization
- **Sensors**: Temperature (Bosch BMP280)
- **Sensors**: Barometric pressure (Bosch BMP280)
- **Sensors**: Light Level (Local) for things like LCD backlight control/night-detection

### Planned/Under Development
- **Sky/Cloud Sensing**: Detect sunny, cloudy, foggy conditions using RGB/blue ratio or spectrum analysis
- **Precipitation/Surface Moisture Detection**
- **Humidity**: Environmental humidity sensing
- **Water Flow/Leak Detection/Cut-off**
- **Smoke Detection**
- **External/Remote Sensors**: Environmental monitoring
- **Predator/Intruder Detection**: By passive infra-red or microwave
- **CO2/O2 Measurements**: Greenhouse/safety monitoring
- **Methane/Alcohol/CO Detection**: Terrariums, safety, gas storage areas
- **Air Quality Monitoring**
- **External Device Controls**: Operate pumps, greenhouse fans, coop doors, etc. using relays or PWM
- **Liquid (Tank) Level Monitoring**: For integration with flow and device controls
- **Dosing**: Water amendments and quality control using possibly peristaltic pumps and flow measurements
- **Data Logging/Data Export**
- **Calibration and Filtering for Sensors**: Particularly for lower-end sensors
- **API Connectivity for PWS Use**
- **OTA Updates**: Remote/Over-the-air firmware updating for remote devices in the field

## Hardware Components

### ESP32 DOIT DevKit board pins, in this case

A reference of the main branch code + pin configurations, for quick hookup.

### LCD Display

1602 in I2C mode:
- VCC	: 5V
- GND : GND
- SDA : GPIO 21 (i2c)
- SCL : GPIO 22 (i2c)

### BMP280 Temperature and Pressure Sensor
DFROBOT / Bosch based BMP280 Barometric and Temperature sensor at hardware address 0x77
- VCC : 3.3V
- GND : GND
- SDA : GPIO 21 (i2c)
- SCL : GPIO 22 (i2c)

### LDR Module
Simple LDR module. If you build your own, then 'analog' is what we use here.
- VCC : 3.3V
- GND : GND
- Analog: 34

## RTC - Realtime Clock
DS1302 based RTC Module with CR2032 button cell.
- VCC : 3.3V
- GND : GND
- CLK : GPIO 25
- DAT : GPIO 26
- RST : GPIO 27

## Software

The Alchemorium firmware/software is being developed in (primarily) C++ using Visual Studio Code and PlatformIO.

### Config.h

`config.h` used to be git ignored, but is now a part of the repository. Values are randomized, so care must be taken to adjust these to your setup.

#### NTP

NTP stands for Network Time Protocol. It's a networking protocol for clock synchronization between computer systems over packet-switched, variable-latency data networks. NTP is crucial for maintaining accurate time across devices connected to the internet.

In the context of *Alchemorium*:
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

Remember, accurate time is crucial for many IoT and data logging applications, making NTP an essential feature of the Alchemorium system.

## Setup and Installation

This will be documented in the future [after prototyping]

## Usage

TODO

## Contributing

See CONTRIBUTING.md

## License

Make sure that a LICENSE or COPYING file accompanies this code.
Alchemorium - ESP32-based environmental monitor, logger, analysis and research station.
Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
License: GNU GPLv3 (see LICENSE/COPYING file for details)

## Contact

Marlon van der Linde <marlonv@pm.me>
