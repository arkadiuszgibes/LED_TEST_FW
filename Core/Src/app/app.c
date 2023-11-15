#include "cmsis_os.h"

#include "app/app.h"
#include "hw/pca9633.h"
#include "app/colors.h"
#include "i2c.h"


/**
 * cube code generator is very sensitive to it's structure so it's good
 * to isolate the logic from cube generated code as much as possible.
 *
 *
 *
 * camelCase notation used by ST wasn't followed because it's easier to track app code.
 * 		it makes clear what does not comes from ST.
 */

/**
 * function increases red in range 0-255
 */
void app_red_seq() {

	// red
	for (uint16_t i = 0; i <= 255; i++) {
		PCA9633_set_color(&hi2c1, i, 0, 0, 0);
		// 50hz refresh, ~ 5 sec per sequence from 0-255
		osDelay(20);
	}
}

/**
 * function increases green in range 0-255
 */
void app_green_seq() {
	// green
	for (uint16_t i = 0; i <= 255; i++) {
		PCA9633_set_color(&hi2c1, 0, i, 0, 0);
		// 50hz refresh, ~ 5 sec per sequence from 0-255
		osDelay(20);
	}
}

/**
 * function increases blue in range 0-255
 */
void app_blue_seq() {
	// blue
	for (uint16_t i = 0; i <= 255; i++) {
		PCA9633_set_color(&hi2c1, 0, 0, i, 0);
		// 50hz refresh, ~ 5 sec per sequence from 0-255
		osDelay(20);
	}
}

/**
 * function increases white in range 0-255
 */
void app_white_seq() {
	// white
	for (uint16_t i = 0; i <= 255; i++) {
		PCA9633_set_color(&hi2c1, 0, 0, 0, i);
		// 50hz refresh, ~ 5 sec per sequence from 0-255
		osDelay(20);
	}
}

/**
 * Function keeps full red and white on for 5000ms
 */
void app_mixed_red_wite_seq() {
	// mix of full red and white
	PCA9633_set_color(&hi2c1, 0xff, 0, 0, 0xff);
	osDelay(5000); // 5 seconds wait

}

/**
 * Function modulates the lightness of RED color in HSL space
 * with step of 0.4%; so it gives us ~ 255 of combinations
 * which is maximum for PCA9633 pwm controller. Of course this is
 * simplification only.
 */
void app_lightness_seq() {
	// lightness of last color
	// it was not specified what color should be used

	uint8_t r, g, b; // our colors

	// initialize colors based on red color
	// in HSL space
	// for red;
	// h = 0; s=1000; l = 0;
	// we start from 0 lightness
	colors_hsl_to_rgb(0, 1000, 0, &r, &g, &b);

	for (uint16_t i = 0; i <= 1000; i += 4) {

		colors_hsl_to_rgb(0, 1000, i, &r, &g, &b);

		PCA9633_set_color(&hi2c1, r, g, b, 0);
		osDelay(20);
	}
}

void app_rainbow_gen() {

	uint8_t r, g, b;
	// init rgb values with initial conditions
	colors_hsl_to_rgb(0, 1000, 500, &r, &g, &b);

	uint32_t hue = 0;
	while (1) {
		// get RGB from HSL space
		// saturation 100% lightness 50%
		colors_hsl_to_rgb(hue, 1000, 500, &r, &g, &b);
		PCA9633_set_color(&hi2c1, r, g, b, 0);

		// clear hue
		if (hue >= 360000)
			hue = 0;

		// 1 deg resolution
		hue += 1000;

		// sleep for 27ms
		// total cycle of rainbow ~10sec
		osDelay(28);

	}
}
