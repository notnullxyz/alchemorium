# MecGrowMancer

## Hardware

### LCD

1602 in I2C mode:

VCC	: 5V
GND : GND
SDA : GPIO 21
SCL : GPIO 22

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


