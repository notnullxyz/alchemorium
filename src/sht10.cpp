/*
 * Alchemorium - ESP32-based Environmental Monitoring and Research Station
 * Copyright (C) 2024 Marlon van der Linde <marlonv@pm.me>
 * License: GNU GPLv3 (see LICENSE/COPYING file for details)
 * 
 * SHT10 Lightweight ALchemorium Library
 */

#include "sht10.h"
#include "serial_debug.h"

// forward declarations
static void sht10TransmissionStart();
static uint8_t sht10ReadByte(bool ack);
static void sht10WriteByte(uint8_t value);
static int sht10ReadStatusRegister();
static int sht10Measure(uint8_t command);

/**
 * @brief Initializes the SHT10 sensor by setting up the data and clock pins.
 * 
 * @return true if the sensor is initialized successfully, false otherwise.
 */
bool initSHT10() {
    pinMode(SHT10_DATA_PIN, INPUT_PULLUP);
    pinMode(SHT10_CLOCK_PIN, OUTPUT);
    digitalWrite(SHT10_CLOCK_PIN, LOW);
    return sht10ReadStatusRegister() != -1;
}

/**
 * @brief Reads the temperature from the SHT10 sensor.
 * 
 * @return Temperature in degrees Celsius, or NAN if an error occurs.
 */
float readSHT10Temperature() {
    int rawData = sht10Measure(0x03); // Temperature command
    if (rawData == -1) return NAN; // Error reading

    // Convert raw data to temperature in Celsius
    return -39.6 + 0.01 * rawData;
}

/**
 * @brief Reads the humidity from the SHT10 sensor.
 * 
 * @return Relative humidity in percentage, or NAN if an error occurs.
 */
float readSHT10Humidity() {
    int rawData = sht10Measure(0x05); // Humidity command
    if (rawData == -1) return NAN; // Error reading

    // Convert raw data to relative humidity
    return -2.0468 + 0.0367 * rawData + -1.5955e-6 * rawData * rawData;
}

/**
 * @brief Initiates the transmission sequence with the SHT10 sensor.
 */
static void sht10TransmissionStart() {
    pinMode(SHT10_DATA_PIN, OUTPUT);
    digitalWrite(SHT10_DATA_PIN, HIGH);
    digitalWrite(SHT10_CLOCK_PIN, HIGH);
    delayMicroseconds(CLOCK_TIMING_DELAY_uS);
    digitalWrite(SHT10_DATA_PIN, LOW);
    delayMicroseconds(CLOCK_TIMING_DELAY_uS);
    digitalWrite(SHT10_CLOCK_PIN, LOW);
    delayMicroseconds(CLOCK_TIMING_DELAY_uS);
    digitalWrite(SHT10_CLOCK_PIN, HIGH);
    delayMicroseconds(CLOCK_TIMING_DELAY_uS);
    digitalWrite(SHT10_DATA_PIN, HIGH);
    delayMicroseconds(CLOCK_TIMING_DELAY_uS);
    digitalWrite(SHT10_CLOCK_PIN, LOW);
}

/**
 * @brief Reads a byte from the SHT10 sensor.
 * 
 * @param ack Boolean indicating whether to send an acknowledgment after reading.
 * @return The byte read from the sensor.
 */
static uint8_t sht10ReadByte(bool ack) {
    uint8_t value = 0;
    pinMode(SHT10_DATA_PIN, INPUT);

    for (int i = 0; i < 8; ++i) {
        digitalWrite(SHT10_CLOCK_PIN, HIGH);
        delayMicroseconds(CLOCK_TIMING_DELAY_uS);
        value = (value << 1) | digitalRead(SHT10_DATA_PIN);
        digitalWrite(SHT10_CLOCK_PIN, LOW);
        delayMicroseconds(CLOCK_TIMING_DELAY_uS);
    }

    pinMode(SHT10_DATA_PIN, OUTPUT);
    digitalWrite(SHT10_DATA_PIN, !ack);
    digitalWrite(SHT10_CLOCK_PIN, HIGH);
    delayMicroseconds(CLOCK_TIMING_DELAY_uS);
    digitalWrite(SHT10_CLOCK_PIN, LOW);
    digitalWrite(SHT10_DATA_PIN, HIGH);

    return value;
}

/**
 * @brief Writes a byte to the SHT10 sensor.
 * 
 * @param value The byte to be written to the sensor.
 */
static void sht10WriteByte(uint8_t value) {
    pinMode(SHT10_DATA_PIN, OUTPUT);

    for (int i = 0; i < 8; ++i) {
        digitalWrite(SHT10_DATA_PIN, (value & 0x80) != 0);
        value <<= 1;
        digitalWrite(SHT10_CLOCK_PIN, HIGH);
        delayMicroseconds(CLOCK_TIMING_DELAY_uS);
        digitalWrite(SHT10_CLOCK_PIN, LOW);
        delayMicroseconds(CLOCK_TIMING_DELAY_uS);
    }

    pinMode(SHT10_DATA_PIN, INPUT);
    digitalWrite(SHT10_CLOCK_PIN, HIGH);
    delayMicroseconds(CLOCK_TIMING_DELAY_uS);
    digitalWrite(SHT10_CLOCK_PIN, LOW);
}

/**
 * @brief Reads the status register of the SHT10 sensor.
 * 
 * @return The status register value, or -1 if an error occurs.
 */
static int sht10ReadStatusRegister() {
    sht10TransmissionStart();
    sht10WriteByte(0x07); // Read status register command
    return sht10ReadByte(false);
}

/**
 * @brief Measures a parameter (temperature or humidity) from the SHT10 sensor.
 * 
 * @param command The command to send for measurement (temperature or humidity).
 * @return The raw measurement value, or -1 if an error occurs.
 */
static int sht10Measure(uint8_t command) {
    sht10TransmissionStart();
    sht10WriteByte(command);

    pinMode(SHT10_DATA_PIN, INPUT);
    for (int i = 0; i < 250; ++i) { // Wait for measurement to complete
        delay(1);
        if (!digitalRead(SHT10_DATA_PIN)) {
            int value = sht10ReadByte(true) << 8;
            value |= sht10ReadByte(false);
            return value;
        }
    }
    return -1; // Error if measurement not ready
}

