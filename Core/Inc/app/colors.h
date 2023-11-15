/*
 * colors.h
 *
 *  Created on: Nov 14, 2023
 *      Author: arek
 */

#ifndef SRC_COLORS_H_
#define SRC_COLORS_H_

#include <stdint.h>

// hsl space to rgb converter without floats
void colors_hsl_to_rgb(const uint32_t h, const uint32_t s, const uint32_t l, uint8_t * r, uint8_t * g, uint8_t * b);

#endif /* SRC_COLORS_H_ */
