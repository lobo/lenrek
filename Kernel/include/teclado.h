#ifndef TECLADO_H	

#define TECLADO_H

#include <stdint.h>

#define ON 1
#define OFF 0

#define INPUT_READY 1
#define NO_INPUT 0

#define C_LOCK			0x3A
#define	ENTER			0x1C
#define LSHIFT_MAKE		0x2A
#define	LSHIFT_BREAK	0xAA
#define RSHIFT_MAKE		0x36
#define RSHIFT_BREAK	0xB6

#define IGNORE			0x99

unsigned char translate_keyboard_input(unsigned char input);

void sys_readKeyboard(char * input_destination);

void to_input_buffer(unsigned char input);

#endif
