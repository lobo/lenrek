#include "RTCuserspace.h"
#include "stdio.h"

char * meses[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", 
					"Junio", "Julio", "Agosto", "Septiembre", "Octubre", 
					"Noviembre", "Diciembre" } ;

extern int read_system_time(int a, unsigned char *c);
extern int set_system_time(int a, unsigned char *c);
extern int tolower(unsigned char c);

void print_system_time()
{
	int i = 0, k = 0;
	char mes;
	unsigned char string[50] ;
	unsigned char rtcdata[7] ;	//{segundo, minuto, hora, dia, mes, anio}

	read_system_time(0, rtcdata);
	
	string[i++] = (rtcdata[2] / 16) + '0'; 				//hora
	string[i++] = (rtcdata[2] & 0xF) + '0';
	string[i++] = ':';
	string[i++] = (rtcdata[1] / 16) + '0'; 				//minutos
	string[i++] = (rtcdata[1] & 0xF) + '0';
	string[i++] = ':';
	string[i++] = (rtcdata[0] / 16) + '0'; 				//segundos
	string[i++] = (rtcdata[0] & 0xF) + '0';

	string[i++] = ' ';									//dia de mes
	string[i++] = (rtcdata[3] / 16) + '0';
	string[i++] = (rtcdata[3] & 0xF) + '0';
	string[i++] = ' ';
	string[i++] = 'd'; string[i++] = 'e'; string[i++] = ' ';

	
	mes = (rtcdata[4]/16)*10 + (rtcdata[4] & 0xF) ;		//mes
	while(meses[mes-1][k] != 0)				
		string[i++] = meses[mes-1][k++];

	string[i++] = ' ';
	string[i++] = 'd'; string[i++] = 'e'; 
	string[i++] = 'l'; string[i++] = ' ';
	string[i++] = '2'; string[i++] = '0'; 
	
	string[i++] = (rtcdata[5] / 16) + '0'; 				//anio
	string[i++] = (rtcdata[5] & 0xF) + '0';
	string[i++] = 0;
	
	printString((char*)string);
	putChar('\n');


}

void change_system_time()
{
	unsigned char rtcdata[6] = {0};	
	unsigned char buffer[100];	
	unsigned char option;
	int hora, minuto, dia, mes, anio;

	printString("Cambiar hora del sistema? (S/N) ");
	
	getString((char*)buffer, 100);	

	option = buffer[0];

	if(tolower(option) != 's' && tolower(option) != 'n')
		INPUT_ERROR_EXIT
	if(tolower(option) == 'n')
	{
		putChar('\n');
		return ;
	}
	
	printString("Ingrese horas: ");				//horas
	if(getInt(&hora, 2) == INPUTERROR)
		INPUT_ERROR_EXIT
	if(hora > 23)
		INPUT_ERROR_EXIT		

	printString("Ingrese minutos: ");			//minutos
	if(getInt(&minuto, 2) == INPUTERROR)
		INPUT_ERROR_EXIT
	if(minuto > 59)
		INPUT_ERROR_EXIT

	printString("Ingrese dia del mes: ");			//dia
	if(getInt(&dia, 2) == INPUTERROR)
		INPUT_ERROR_EXIT
	if(dia > 31)
		INPUT_ERROR_EXIT

	printString("Ingrese numero de mes: ");			//mes
	if(getInt(&mes, 2) == INPUTERROR)
		INPUT_ERROR_EXIT
	if(mes > 12)
		INPUT_ERROR_EXIT

	printString("Ingrese los dos ultimos digitos del anio: ");		//anio
	if(getInt(&anio, 2) == INPUTERROR)
		INPUT_ERROR_EXIT

	
	if( mes==2 && (dia > 29) )
		FECHA_INVALIDA
	if( mes==2 && (anio%4 != 0) && (dia > 28) )
		FECHA_INVALIDA
	if( (mes==4 || mes==6 || mes==9 || mes==11) && dia > 30)
		FECHA_INVALIDA

	rtcdata[0] = 0;
	rtcdata[1] = tobcd(minuto);
	rtcdata[2] = tobcd(hora);
	rtcdata[3] = tobcd(dia);
	rtcdata[4] = tobcd(mes);
	rtcdata[5] = tobcd(anio);

	set_system_time(0, rtcdata);
	
}

unsigned char tobcd(int input)
{
	unsigned char output_char = 0;

	unsigned char aux = input / 10;
	
	aux = aux * 16;
	aux = aux & 0xF0;

	output_char += aux;

	aux = input % 10;
	aux = aux & 0x0F;

	output_char += aux;

	return output_char;
}
	