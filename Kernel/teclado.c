#include <teclado.h>

int lshift_state = OFF;
int rshift_state = OFF;
int capslock_state = OFF;

int p;
unsigned char input_buffer;
unsigned char buffer_status = NO_INPUT;


/* traduce el input del teclado en los valores ascii correspondientes */
unsigned char translate_keyboard_input(unsigned char input)
{
	unsigned char valor_ascii;

	int shifted = lshift_state || rshift_state ;
	
	int cshifted = shifted;	// characteres afectados por caps lock
	
	if(capslock_state == ON)
		cshifted = !cshifted;
	
	switch(input)
	{
			case C_LOCK: capslock_state = !capslock_state; 	break;
			case LSHIFT_MAKE: lshift_state = ON; 		break;
			case LSHIFT_BREAK: lshift_state = OFF;		break;
			case RSHIFT_MAKE: rshift_state = ON; 		break;
			case RSHIFT_BREAK: rshift_state = OFF; 		break;
			
			case 0x1E: if(cshifted)	valor_ascii = 'A';
				   else 	valor_ascii = 'a'; break;
			case 0x30: if(cshifted)	valor_ascii = 'B'; 
				   else		valor_ascii = 'b'; break;
			case 0x2E: if(cshifted)	valor_ascii = 'C'; 
				   else		valor_ascii = 'c'; break;
			case 0x20: if(cshifted)	valor_ascii = 'D'; 
				   else		valor_ascii = 'd'; break;
			case 0x12: if(cshifted)	valor_ascii = 'E'; 
				   else		valor_ascii = 'e'; break;
			case 0x21: if(cshifted)	valor_ascii = 'F'; 
				   else		valor_ascii = 'f'; break;
			case 0x22: if(cshifted)	valor_ascii = 'G'; 
				   else		valor_ascii = 'g'; break;
			case 0x23: if(cshifted)	valor_ascii = 'H'; 
				   else		valor_ascii = 'h'; break;
			case 0x17: if(cshifted)	valor_ascii = 'I'; 
				   else		valor_ascii = 'i'; break;
			case 0x24: if(cshifted)	valor_ascii = 'J'; 
				   else		valor_ascii = 'j'; break;
			case 0x25: if(cshifted)	valor_ascii = 'K'; 
				   else		valor_ascii = 'k'; break;
			case 0x26: if(cshifted)	valor_ascii = 'L'; 
				   else		valor_ascii = 'l'; break;
			case 0x32: if(cshifted)	valor_ascii = 'M'; 
				   else		valor_ascii = 'm'; break;
			case 0x31: if(cshifted)	valor_ascii = 'N'; 
				   else		valor_ascii = 'n'; break;
			case 0x18: if(cshifted)	valor_ascii = 'O'; 
				   else		valor_ascii = 'o'; break;
			case 0x19: if(cshifted)	valor_ascii = 'P'; 
				   else		valor_ascii = 'p'; break;
			case 0x10: if(cshifted)	valor_ascii = 'Q'; 
				   else		valor_ascii = 'q'; break;
			case 0x13: if(cshifted)	valor_ascii = 'R'; 
				   else		valor_ascii = 'r'; break;
			case 0x1F: if(cshifted)	valor_ascii = 'S'; 
				   else		valor_ascii = 's'; break;
			case 0x14: if(cshifted)	valor_ascii = 'T'; 
				   else		valor_ascii = 't'; break;
			case 0x16: if(cshifted)	valor_ascii = 'U'; 
				   else		valor_ascii = 'u'; break;
			case 0x2F: if(cshifted)	valor_ascii = 'V'; 
				   else		valor_ascii = 'v'; break;
			case 0x11: if(cshifted)	valor_ascii = 'W'; 
				   else		valor_ascii = 'w'; break;
			case 0x2D: if(cshifted)	valor_ascii = 'X'; 
				   else		valor_ascii = 'x'; break;
			case 0x15: if(cshifted)	valor_ascii = 'Y'; 
				   else		valor_ascii = 'y'; break;
			case 0x2C: if(cshifted)	valor_ascii = 'Z'; 
				   else		valor_ascii = 'z'; break;
			case 0x02: if(shifted)	valor_ascii = '!'; 
				   else		valor_ascii = '1'; break;
			case 0x03: if(shifted)	valor_ascii = '@'; 
				   else		valor_ascii = '2'; break;
			case 0x04: if(shifted)	valor_ascii = '#'; 
				   else		valor_ascii = '3'; break;
			case 0x05: if(shifted)	valor_ascii = '$'; 
				   else		valor_ascii = '4'; break;
			case 0x06: if(shifted)	valor_ascii = '%'; 
				   else		valor_ascii = '5'; break;
			case 0x07: if(shifted)	valor_ascii = '^'; 
				   else		valor_ascii = '6'; break;
			case 0x08: if(shifted)	valor_ascii = '&'; 
				   else		valor_ascii = '7'; break;
			case 0x09: if(shifted)	valor_ascii = '*'; 
				   else		valor_ascii = '8'; break;
			case 0x0A: if(shifted)	valor_ascii = '('; 
				   else		valor_ascii = '9'; break;
			case 0x0B: if(shifted)	valor_ascii = ')'; 
				   else		valor_ascii = '0'; break;
			case 0x0C: if(shifted)	valor_ascii = '_'; 
				   else		valor_ascii = '-'; break;
			case 0x0D: if(shifted)	valor_ascii = '+'; 
				   else		valor_ascii = '='; break;
			case 0x29: if(shifted)	valor_ascii = '~'; 
				   else		valor_ascii = '`'; break;
			case 0x1A: if(shifted)	valor_ascii = '{'; 
				   else		valor_ascii = '['; break;
			case 0x1B: if(shifted)	valor_ascii = '}'; 
				   else		valor_ascii = ']'; break;
			case 0x2B: if(shifted)	valor_ascii = '|'; 
				   else		valor_ascii = '\\'; break;
			case 0x27: if(shifted)	valor_ascii = ':'; 
				   else		valor_ascii = ';'; break;
			case 0x28: if(shifted)	valor_ascii = '"'; 
				   else		valor_ascii = '\''; break;
			case 0x33: if(shifted)	valor_ascii = '<'; 
				   else		valor_ascii = ','; break;
			case 0x34: if(shifted)	valor_ascii = '>'; 
				   else		valor_ascii = '.'; break;
			case 0x35: if(shifted)	valor_ascii = '?'; 
				   else		valor_ascii = '/'; break;
			case 0x1C: if(shifted)	valor_ascii = '\n'; 
				   else		valor_ascii = '\n'; break;
			case 0x39: if(shifted)	valor_ascii = ' '; 
				   else		valor_ascii = ' '; break;
			case 0x0E: if(shifted)	valor_ascii = '\b'; 
				   else		valor_ascii = '\b'; break;

			default: valor_ascii = IGNORE;
	}
		
	return valor_ascii;
}

/* envia a user space el ultimo valor ascii ingresado. si no hay ningun valor
   disponible envia cero */
void sys_readKeyboard(char * inputdestination)
{

	if(buffer_status == NO_INPUT)
		inputdestination[0] = NO_INPUT;
	else
	{
		inputdestination[0] = input_buffer;
		buffer_status = NO_INPUT;
	}
}

/* coloca un valor ascii dentro del input buffer */
void to_input_buffer(unsigned char input)
{
	input_buffer = input;
	buffer_status = INPUT_READY;
}

