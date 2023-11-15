#include "hw/pca9633.h"
#include "stm32f1xx_hal_i2c.h"

/**
 * Initialize i2c target device
 *
 * I2c used in blocking mode, there is only single i2c device in our system.
 */
void PCA9633_Init(I2C_HandleTypeDef *hi2c) {


	/**
	 * Target device will be used in autoincremenet mode for individual PWM channels only.
	 */

	// sey hello and reset
	HAL_I2C_Master_Transmit(hi2c, ADDR_SW_RESET, 0, 0, HAL_MAX_DELAY);

    uint8_t data[2];

    // select ctrl reg with mode1 reg
    data[0] = CTRL_REG_MODE1;
    // enable autoincrement AI2 bit in MODE1 reg
    data[1] = MODE1_AI2EN;

    // send config
    HAL_I2C_Master_Transmit(hi2c, ADDR_PHY_TARGET, data, 2, HAL_MAX_DELAY);

    // Set MODE2 reg
    data[0] = CTRL_REG_MODE2;
    // Normal mode, outputs to open drain
    data[1] = 0;

    // send config
    HAL_I2C_Master_Transmit(hi2c, ADDR_PHY_TARGET, data, 2, HAL_MAX_DELAY);
}

/**
 * Function sets 4 channels duty cycle of RGBW LED controller. Each color can be set individualy.
 * based on transaction description from datasheet.
 */
void PCA9633_set_color(I2C_HandleTypeDef *hi2c, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    uint8_t data[5];

    data[0] = CTRL_REG_AI_RGBA; // autoincrement for pwm[0-3]
    data[1] = red;		// set value of PWM0 channel
    data[2] = green;	// set value of PWM1 channel
    data[3] = blue;		// set value of PWM2 channel
    data[4] = white;	// set value of PWM3 channel

    HAL_I2C_Master_Transmit(hi2c, ADDR_PHY_TARGET, data, 5, HAL_MAX_DELAY);
}
