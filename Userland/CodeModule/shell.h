#ifndef SHELL_H
#define SHELL_H

#define INPUT_READY 1
#define NO_INPUT 0
#define PROMPT ">> "
#define PROMPT2 "\n>> "
#define PROMPTLENGTH 3

#define VALID 1
#define NOT_VALID 0

#define TYPEHELP "command not found: type 'help' for command list\n"

void shell();

void help();

int parse_command(char * s1, char * s2);

void screensavertimer();

void beep();

void music();

#endif
