#ifndef ADAFRUIT_ADS7830_H
#define ADAFRUIT_ADS7830_H

#include <Adafruit_I2CDevice.h>

// Default I2C Address
#define ADS7830_I2C_ADDR 0x48 ///< Default I2C Address

// Power-Down Selection Enum
typedef enum {
  POWER_DOWN_BETWEEN_CONVERSIONS =
      0x00, ///< Power Down Between A/D Converter Conversions
  INTERNAL_REF_OFF_ADC_ON =
      0x01, ///< Internal Reference OFF and A/D Converter ON
  INTERNAL_REF_ON_ADC_OFF =
      0x02,                     ///< Internal Reference ON and A/D Converter OFF
  INTERNAL_REF_ON_ADC_ON = 0x03 ///< Internal Reference ON and A/D Converter ON
} ad7830PowerDownSelection;

// Channel Selection Control Enum
typedef enum {
  DIFF_CH0_CH1 = 0x00, ///< Differential CH0-CH1
  DIFF_CH2_CH3 = 0x01, ///< Differential CH2-CH3
  DIFF_CH4_CH5 = 0x02, ///< Differential CH4-CH5
  DIFF_CH6_CH7 = 0x03, ///< Differential CH6-CH7
  DIFF_CH1_CH0 = 0x04, ///< Differential CH1-CH0
  DIFF_CH3_CH2 = 0x05, ///< Differential CH3-CH2
  DIFF_CH5_CH4 = 0x06, ///< Differential CH5-CH4
  DIFF_CH7_CH6 = 0x07, ///< Differential CH7-CH6
  SINGLE_CH0 = 0x08,   ///< Single-Ended CH0
  SINGLE_CH2 = 0x09,   ///< Single-Ended CH2
  SINGLE_CH4 = 0x0A,   ///< Single-Ended CH4
  SINGLE_CH6 = 0x0B,   ///< Single-Ended CH6
  SINGLE_CH1 = 0x0C,   ///< Single-Ended CH1
  SINGLE_CH3 = 0x0D,   ///< Single-Ended CH3
  SINGLE_CH5 = 0x0E,   ///< Single-Ended CH5
  SINGLE_CH7 = 0x0F    ///< Single-Ended CH7
} ad7830ChannelSelectionControl;

class Adafruit_ADS7830 {
public:
  Adafruit_ADS7830();
  bool begin(uint8_t i2c_addr = ADS7830_I2C_ADDR, TwoWire *theWire = &Wire);
  int16_t readADCsingle(uint8_t ch,
                        ad7830PowerDownSelection pd = INTERNAL_REF_ON_ADC_ON);
  uint8_t
  readADCdifferential(uint8_t ch,
                      ad7830PowerDownSelection pd = INTERNAL_REF_ON_ADC_ON);

private:
  Adafruit_I2CDevice *i2c_dev; // I2C device
};

#endif // ADAFRUIT_ADS7830_H
