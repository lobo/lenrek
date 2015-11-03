#ifndef RTCUSERSPACE_H
#define RTCUSERSPACE_H

#define INPUTERROR 0
#define INPUT_ERROR_EXIT { printString("Input Errado!\n");}
#define FECHA_INVALIDA { printString("Fecha Invalida!\n");}

void print_system_time();

void change_system_time();

unsigned char tobcd(int);

#endif
