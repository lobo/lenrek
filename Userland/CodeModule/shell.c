#include "stdio.h"
#include "shell.h"
#include "RTCuserspace.h"
#include "string.h"

#define CANT_COMMANDS_SHELL 7

typedef void (*fptr)(void);

//comandos
char * shell_commands[] = {"systime", "setsystime", "changecolor",
						   "clear", "screensavertimer", "playsound", "help"} ;

//punteros a funciones correspondientes
fptr shell_functions[] = {print_system_time, change_system_time,
						  change_text_color, clearscreen,
						  screensavertimer, playsound, help} ;

int command;
char input_char;
char command_buffer[BUFFERLENGTH] = {0};


/* funcion del shell */
void shell()
{
	int i;

	while(1)
	{
		command = NOT_VALID;
		printString(PROMPT);
		getString(command_buffer, BUFFERLENGTH);

		for(i = 0 ; i < CANT_COMMANDS_SHELL && command == NOT_VALID ; i++)
		{
			if( parse_command(shell_commands[i], command_buffer) )
			{
				command = VALID;
				(*(shell_functions[i]))();
			}
		}
		if(command == NOT_VALID)
				printString(TYPEHELP);

	}
}

/* interpreta el comando ingresado */
int parse_command(char * s1, char * s2)
{
	int i = 0;

	while(s1[i] != 0)
	{
		if(s1[i] != s2[i])
			return 0;
		i++;
	}

	return 1;
}

/* funcion de ayuda */
void help()
{
	printString("--------------------< shell commands >--------------------\n");
	printString("systime - mostrar la hora y fecha del sistema \n");
	printString("setsystime - modificar la hora y fecha del sistema\n");
	printString("changecolor - cambiar los colores de texto y fondo\n");
	printString("help - mostrar lista de comandos\n");
	printString("clear - borrar el texto de la pantalla\n");
	printString("screensavertimer - setear tiempo de protector de pantallas\n");
	printString("playsound - reproduce un sonido durante un tiempo determinado\n");
	printString("----------------------------------------------------------\n");

	return;
}

/* modifica el tiempo de activacion del screensaver mediante system call */
void screensavertimer()
{
	int n;

	printString("Ingrese en segundos un tiempo de ");
	printString("activacion para el salvapantallas: ");
	if(getInt(&n, 9) == INPUTERROR)
		INPUT_ERROR_EXIT

	set_ss_timer(n); // system call
}
