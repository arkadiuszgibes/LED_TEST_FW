/*
 * pca9633.h
 *
 *  Created on: Nov 14, 2023
 *      Author: arek
 */

#ifndef INC_PCA9633_H_
#define INC_PCA9633_H_

#include "stm32f1xx.h"

/**
 * usefull addresses
 */

#define ADDR_SW_RESET 	0x6
#define ADDR_LED_ALL	0xe0
#define ADDR_GEN_CALL	0x0

// physical addres of our target, A0 to VCC, A1-A6 to gnd, fixed by HW design
#define ADDR_PHY_TARGET 0x2

/**
 * usefull register numbers
 */
#define REG_MODE1 0x00
#define REG_MODE2 0x01
#define REG_PWM0 0x02
#define REG_PWM1 0x03
#define REG_PWM2 0x04
#define REG_PWM3 0x05

#define MODE2_MASK 0
#define MODE1_MASK 0

/**
 * Control reg masks configs
 */

#define CTRL_REG_MODE1 REG_MODE1
#define CTRL_REG_MODE2 REG_MODE2

#define CTRL_REG_MANUAL_R REG_PWM0
#define CTRL_REG_MANUAL_G REG_PWM1
#define CTRL_REG_MANUAL_B REG_PWM2
#define CTRL_REG_MANUAL_W REG_PWM3

// mask for auto incremnet
// for individual brightness regs only
#define AI_RGBA_MASK 0x5

// ctrl register value for rgbw transaction
#define CTRL_REG_AI_RGBA AI_RGBA_MASK << 5

// mode1 mask
#define MODE1_AI2EN 0x80


void PCA9633_Init(I2C_HandleTypeDef *hi2c);
void PCA9633_set_color(I2C_HandleTypeDef *hi2c, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);


#endif /* INC_PCA9633_H_ */
