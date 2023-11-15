#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/**
 *
 * Function convers HSL space to RGB using 32 bits integers
 *
 *
 * arm cortex m3 is 32 bit arch so it's better to use uint32 instead of floats. We don't have fpu on board
 *
 *	all values of HSL are scaled by 1000; so we have
 *	hue 0-36000 range
 *	lightnese 0-1000
 *	saturation 0-1000
 */

void colors_hsl_to_rgb(const uint32_t h, const uint32_t s, const uint32_t l, uint8_t * red, uint8_t * green, uint8_t * blue) {


	uint8_t r,g,b;

	// calc c,x,m
	int32_t c = ( 1000 - abs( (2 * (int32_t)l - 1000 ) ) ) * (int32_t)s ;
	int32_t x = c * ( 1000 - abs( ( ( (int32_t)h / 60000) % 2 ) - 1000 ) );
	int32_t m = l - c / 2;

	// do math based on hue angle
	if (h >= 0 && h < 60000) {
		r = c;
		g = x;
		b = 0;
	} else if (h >= 60000 && h < 120000) {
		r = x;
		g = c;
		b = 0;
	} else if (h >= 120000 && h < 180000) {
		r = 0;
		g = c;
		b = x;
	} else if (h >= 180000 && h < 240000) {
		r = 0;
		g = x;
		b = c;
	} else if (h >= 240000 && h < 300000) {
		r = x;
		g = 0;
		b = c;
	} else {
		r = c;
		g = 0;
		b = x;
	}

	// normalize to 255;
	r = (r + m) * 255;
	g = (g + m) * 255;
	b = (b + m) * 255;

	// get range of rgb [0-255]
	*red = r/1000;
	*green = g/1000;
	*blue = b/1000;
}
