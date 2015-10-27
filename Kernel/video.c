#include <video.h>

char * video = (char *)0xB8000;

char displaystate[ROWS*COLS*2];

static int cursor_offset = 0;

unsigned char color = 0x0C;

/* imprime 1 caracter en pantalla */
void printchar(const char c)
{
	if(c == '\b')
	{
		video[--cursor_offset] = color;
		video[--cursor_offset] = ' ';
	}
	else if(c == '\n')
	{
		if( cursor_offset < COLS*2*(ROWS-1) )		
			cursor_offset += COLS*2 - ( cursor_offset % (COLS*2) );
		else
		{
			scrolldown();
			cursor_offset -= cursor_offset % (COLS*2);
		}
	}
	else
	{
		video[cursor_offset++] = c;
		video[cursor_offset++] = color;
	}
}

/* borra el texto de la pantalla */
void clearscreen(void)
{
	int i;
	for( i = 0 ; i < ROWS*COLS ; i++ )
	{
		video[i*2] = ' ';
		video[i*2 + 1] = color;
	}

	cursor_offset = 0;
}

/* corre el texto ingresado anteriormente para arriba una fila */
void scrolldown()
{
	int i, j;
	for( i = 0 ; i < (ROWS - 1) ; i++ )
	{
		for( j = 0 ; j < COLS*2 ; j++ )
			video[COLS*2*i + j] = video[COLS*2*(i+1) + j];
	}
	for( j = 0 ; j < COLS ; j++ )
	{
		video[COLS*2*(ROWS - 1) + j*2] = ' ';
		video[COLS*2*(ROWS - 1) + j*2 + 1] = color;
	}

}

/* guarda la informacion en la pantalla */
void savedisplaystate()
{
	int i;

	for(i=0 ; i < ROWS*COLS*2 ; i++)
		displaystate[i] = video[i];
}

/* vuelve a cargar la informacion a la pantalla */
void loaddisplaystate()
{
	int i;

	for(i=0 ; i < ROWS*COLS*2 ; i++)
		video[i] = displaystate[i];
}

/* imprime un string de longitud size */
void sys_displayWrite(const char * string, unsigned long size)
{
	int i;

	for(i=0 ; i < size ; i++)
		printchar(string[i]);

}

/* cambia el color de texto y fondo de la pantalla */
void sys_changeColor(const char value)
{
	int i;

	color = value;

	for(i = 0 ; i < ROWS*COLS ; i++)
		{
			video[2*i+1] = color;
		}
}




