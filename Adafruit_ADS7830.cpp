/*!
 * @file Adafruit_ADS7830.cpp
 *
 * @mainpage Adafruit ADS7830 ADC library
 *
 * @section intro_sec Introduction
 *
 * This is the documentation for Adafruit's ADS7830 driver for the
 * Arduino platform. It is designed specifically to work with the
 * Adafruit ADS7830 breakout: https://www.adafruit.com/product/xxxx
 *
 * These sensors use I2C to communicate, 2 pins (SCL+SDA) are required
 * to interface with the board.
 *
 * Adafruit invests time and resources providing this open-source code.
 * Please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section dependencies Dependencies
 * - Adafruit_BusIO
 *
 * @section author Author
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * @section license License
 * BSD license, all text here must be included in any redistribution.
 *
 */

#include "Adafruit_ADS7830.h"

/**
 * @brief Construct a new Adafruit_ADS7830 object.
 *
 * Initializes the i2c_dev member variable to nullptr.
 */
Adafruit_ADS7830::Adafruit_ADS7830() { i2c_dev = nullptr; }

/**
 * @brief Initialize the ADS7830 chip.
 *
 * @param i2c_addr I2C address of the ADS7830 chip.
 * @param theWire Pointer to the TwoWire object.
 * @return true if initialization is successful, false otherwise.
 */
bool Adafruit_ADS7830::begin(uint8_t i2c_addr, TwoWire *theWire) {
  if (i2c_dev) {
    delete i2c_dev;
  }

  i2c_dev = new Adafruit_I2CDevice(i2c_addr, theWire);

  return i2c_dev->begin();
}

/**
 * @brief Read ADC value in single-ended mode.
 *
 * @param ch Channel to read from (0-7).
 * @param pd Power-down selection mode.
 * @return ADC value or 0 if read failed.
 */
int16_t Adafruit_ADS7830::readADCsingle(uint8_t ch,
                                        ad7830PowerDownSelection pd) {
  if (ch > 7) {
    return 0; // Invalid channel
  }

  uint8_t commandByte = 0;

  if (ch % 2 == 0) {
    commandByte |= (SINGLE_CH0 + (ch / 2));
  } else {
    commandByte |= (SINGLE_CH1 + ((ch - 1) / 2));
  }
  commandByte <<= 4;

  commandByte |= (pd << 2); // Set power-down bits

  uint8_t adcValue;
  if (!i2c_dev->write_then_read(&commandByte, 1, &adcValue, 1)) {
    return -1; // Write-then-read failed
  }

  return adcValue;
}

/**
 * @brief Read ADC value in differential mode.
 *
 * @param ch Positive channel for differential reading (0-7).
 * @param pd Power-down selection mode.
 * @return ADC value or 0 if read failed.
 *
 * The negative channel for differential reading is determined by the chip and
 * is fixed. For example, if ch is 0, the negative channel will be 1.
 */
uint8_t Adafruit_ADS7830::readADCdifferential(uint8_t ch,
                                              ad7830PowerDownSelection pd) {
  if (ch > 7) {
    return 0; // Invalid channel
  }

  uint8_t commandByte = 0;

  // Set channel bits for differential mode
  if (ch % 2 == 0) {
    commandByte |= (DIFF_CH0_CH1 + (ch / 2));
  } else {
    commandByte |= (DIFF_CH0_CH1 + ((ch - 1) / 2));
  }
  commandByte <<= 4;

  commandByte |= (pd << 2); // Set power-down bits

  uint8_t adcValue;
  if (!i2c_dev->write_then_read(&commandByte, 1, &adcValue, 1)) {
    return 0; // Write-then-read failed
  }

  return adcValue;
}
