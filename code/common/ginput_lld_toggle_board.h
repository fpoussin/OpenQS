/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_TOGGLE_BOARD_H
#define _GDISP_LLD_TOGGLE_BOARD_H

//#error "GINPUT Toggle Pal Driver: You need to define your board definitions"

#define SW1_MASK 13
#define SW2_MASK 14
#define SW3_MASK 15

#define GINPUT_TOGGLE_NUM_PORTS		3		// The total number of toggle inputs
#define GINPUT_TOGGLE_CONFIG_ENTRIES	1			// The total number of GToggleConfig entries

#define GINPUT_TOGGLE_SW1			0			// Switch 1
#define GINPUT_TOGGLE_UP				1			// Joystick Up
#define GINPUT_TOGGLE_DOWN			2			// Joystick Down

#define GINPUT_TOGGLE_DECLARE_STRUCTURE()								\
	const GToggleConfig GInputToggleConfigTable[GINPUT_TOGGLE_CONFIG_ENTRIES] = {	\
		{GPIOC,													\
		SW1_MASK|SW2_MASK|SW3_MASK,								\
		SW1_MASK|SW2_MASK|SW3_MASK,								\
		PAL_MODE_INPUT},											\
	}

#endif /* _GDISP_LLD_TOGGLE_BOARD_H */
