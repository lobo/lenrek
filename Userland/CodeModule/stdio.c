#include"stdio.h"
#include"string.h"
#include"lib.h"

#define MAX_DATA 100

static char buffer[1024] = { 0 };


/* llama al system call read para recibir el estado del input buffer */
void get_input(char * c)
{
	read(1, c); // system call
}

/* invoca un getString de longitud 1 */
char getChar()
{

	getString(buffer, 1);

	return buffer[0];
}

/* llama al system call write con longitud 1 */
void putChar(char c)
{
	write(1, &c); // system call
}

/* imprime un string mediante system call write */
void printString(const char * str)
{
	write(strlen(str), (void *)str); // system call
}

/* utiliza el system call read dentro de la funcion get_input para armar
   un string de caracteres ingresados por teclado hasta el '\n' inclusive,
   a medida que los va imprimiendo meidante putChar. Ignora backspaces que
   borrarian el texto ya escrito en pantalla, por ejemplo un prompt del
   shell */
void getString(char *buffer, const int size)
{
	int flag = ON, len = 0;
	char input_char;

	while(flag == ON)
	{
		get_input(&input_char);

		if(input_char != NO_INPUT)
		{
			if( ! (input_char == '\b' && len == 0) )
			{
				putChar(input_char);

				if(input_char != '\b')
					buffer[len++] = input_char;

				if(input_char == '\b')
					len--;

				if(input_char == '\n' || len == size)
					flag = OFF;

			}
		}
	}

	buffer[len++] = 0;
}

/* recibe un string mediante getString y lo traduce en un integer. Devuelve 0
   si el string contiene caracteres que no son digitos */
int getInt(int * num, const int size)
{
	int i = 0, n = 0;
	char buffer[100];

	getString(buffer, 100);

	while(buffer[i] != '\n')
	{
		if(! isdigit(buffer[i]) )
			return 0;

		n = n*10;
		n += buffer[i] - '0';
		i++;
	}

	*num = n;

	return 1;
}

/* recibe un string y devuelve un integer. si un caracter no es un digito
   devuelve -1 */
int stoi(char * s)
{
	int num = 0;

	while(*s != 0 && num >= 0)
	{
		num = num*10;
		if( isdigit(*s) )
			num = num + (*s - '0');
		else
			num = -1;
		s++;
	}
	return num;
}

/* devuelve 1 si el caracter ingresado es un digito, y sino devuelve 0 */
int isdigit(unsigned char c)
{
	return (c >= '0' && c <= '9');
}

/* traduce un string de un numero hexadecimal */
int htoi(const char *str, int *result)
{
	int c;

	if (str[0] == '0' && str[1] == 'x')
		str += 2;

	for (*result = 0; (c = *str) != 0; str++)
	{
		if ( c >= 'a' && c <= 'f')
			c = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			c = c - 'A' + 10;
		else if (c >= '0' && c <= '9')
			c -= '0';
		else
			return 0;

		*result = *result << 4 | c;
	}
	return 1;
}

void printf(const char *fmt, ...)
{
	int num;
	char c;
	char * s;
	va_list va;
	char ch;

	va_start(va, fmt); //Asigno en va un puntero a la lista de argumentos

	while ( (ch = *(fmt++)) )
	{
		while ( ch != '%' && ch != 0 && ch != '\n' )
		{
			putChar(ch);
			ch = *(fmt++);
		}
		if (ch == '%')
		{
			ch = *(fmt++);
			switch (ch)
			{
				case 0: putChar('%'); return;
				case 'u':
				case 'd':
				case 'D':
				case 'x':
				case 'X':
					//Levanto el siguiente argumento sabiendo que es un int
					num = (int)va_arg(va, int);
					//Si el numero pasado por arg en negativo imprimo '-'
					if ( num < 0)
					{
							num = -num;
							putChar('-');
					}
				   if(ch == 'u' || ch == 'd');
						printDec(num);
					if(ch == 'x' || ch == 'X')
						printHex(num);
					break;
				case 'c' :
					//Levanto el siguiente argumento sabiendo que es un char
					c = (char)va_arg(va, int);
					putChar(c);
					break;
				case 's' :
					s = (char *)va_arg(va, int);
					printString(s);
					break;
				case '%' :

				default:
					break;
			}

		}
	}
	va_end(va);
}

int scanf(const char *fmt, ...)
{
    int i = 0, k = 0;
    int * n = 0;
    char * c = 0;
    char * s = 0;
    char hexa_string[100];

    va_list argp;
    va_start(argp, fmt);

    for(i = 0; fmt[i] != '\0'; i++)
    {
        if(fmt[i] == '%')
        {
            i++;
            switch(fmt[i])
            {
                case '\0':
                    printString("Formato invalido.\n");
                    break;

                case 'd':
                    n = va_arg(argp, int *);
                    getInt(n, 100);
                    break;

                case 'c':
                    c = va_arg(argp, char *);
                    getString(c, 1);
                    break;

                case 's':
                    s = va_arg(argp, char *);
                    getString(s, 100);
                    break;

                case 'x':
                	n = va_arg(argp, int *);
                	getString(hexa_string, 100);
                	while(hexa_string[k] != '\n')
                		k++;
                	hexa_string[k] = 0;
                	if(!htoi(hexa_string, n))
                		INPUT_ERROR_EXIT
                	break;

                default:
                    printString("Formato invalido.\n");
            }
        }

    }

    va_end(argp);
    return 1;
}

/* cambia los colores de texto y fondo de la pantalla mediante system call */
void change_text_color()
{
	unsigned char n;
	unsigned char colorbuff[100] = {0};
	unsigned char color_texto = 0, color_fondo = 0, valores = 0;

	printString("0 - Negro       8 - Gris Oscuro\n");
	printString("1 - Azul        9 - Azul Claro\n");
	printString("2 - Verde       A - Verde Claro\n");
	printString("3 - Celeste     B - Celeste Claro\n");
	printString("4 - Rojo        C - Rojo Claro\n");
	printString("5 - Violeta     D - Rosa\n");
	printString("6 - Marron      E - Amarillo\n");
	printString("7 - Gris Claro  F - Blanco\n");

	printString("Elija un color de texto: ");
	getString(colorbuff, 100);
	n = colorbuff[0];
	if(n >= '0' && n <= '9')
	{
		color_texto = colorbuff[0] - '0';
		valores += color_texto;
	}
	else if(n >= 'A' && n <= 'F')
	{
		color_texto = n - 'A' + 10;
		valores += color_texto;
	}
	else
		INPUT_ERROR_EXIT

	printString("Elija un color de fondo: ");
	getString(colorbuff, 100);
	n = colorbuff[0];
	if(n >= '0' && n <= '9')
	{
		color_fondo = n - '0';
		valores += color_fondo*16;
	}
	else if(n >= 'A' && n <= 'F')
	{
		color_fondo = n - 'A' + 10;
		valores += color_fondo*16;
	}
	else
		INPUT_ERROR_EXIT

	if(color_texto == color_fondo)
		{
			printString("El texto y el fondo tienen que");
			printString(" tener colores distintos!\n");
			return ;
		}

	if(color_texto == color_fondo)
	{
		printString("El texto y el fondo tienen que");
		printString(" tener colores distintos!\n");
		return ;
	}

	change_color(valores);  // system call
}

/* borra el texto de la pantalla mediante system call */
void clearscreen()
{
		clear_screen();
}

/* informa mediante system call el estado del flag de user space timertick */
void timertick()
{
		char flag;

		timer_tick(&flag); //system call
}

/* This function plays music */
void play_music()
{
	play_music_sys();
	return;
}

/* This function plays a sound */
void play_beep(int freq, int time)
{
	play_beep_sys(freq, time);
	return;
}

/********** Funciones de la catedra **********/
void saveDec(int * value, char * buf)
{
	uintToBase(*value, buf, 16);
	*value = stoi(buf);
}

void saveHex(int * value, char * buf)
{
	uintToBase(*value, buf, 16);
	*value = stoi(buf);
}

void printDec(int value)
{
	printBase(value, 10);
}

void printHex(int value)
{
	printBase(value, 16);
}

void printBin(int value)
{
	printBase(value, 2);
}

void printBase(int value, int base)
{
    uintToBase(value, buffer, base);
    printString(buffer);
}

int uintToBase(int value, char * buffer, int base)
{
	char *p = buffer;
	char *p1, *p2;
	int digits = 0;

	//Calculate characters for each digit
	do
	{
		int remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

