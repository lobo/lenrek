#include <screensaver.h>
#include <video.h>
#include <idt.h>

unsigned int timer = 0;

unsigned int mario_timer = 0;

unsigned int mario_vuelve = 0;

unsigned int screensaverstatus = OFF;

unsigned int ss_timeout = 20*TICKS_PER_SECOND;  // 20 segundos por default


/* resetea el timer a 0. Si el screensaver se encontraba activado lo desactiva
   y le devuelve a la pantalla el estado anterior al screensaver */
int suppress_screensaver()
{
	timer = 0;
	
	if(screensaverstatus == ON)
	{
		loaddisplaystate();
		screensaverstatus = OFF;
		mario_timer = 0;
		return SS_WAS_ON;
	}
	
	return SS_IS_OFF;
}

/* aumenta el timer con cada interrupcion del timer tick hasta que alcanza el
   valor ss_timeout y luego guarda el estado de la pantalla y activa el 
   screensaver */
void screensavertimer()
{
	if(screensaverstatus == OFF);
		timer++;
		
	if(timer == ss_timeout && screensaverstatus == OFF)
	{
		screensaverstatus = ON;
		savedisplaystate();
		displayscreensaver();
	}

	if(screensaverstatus == ON)
		displayscreensaver();
	
}

/* modifica el valor de la variable ss_timeout */
void set_ss_timeout(unsigned long n)
{
		ss_timeout = n*TICKS_PER_SECOND;
}

/* la funcion del screensaver, invocada con cada timer tick */
void displayscreensaver()
{
	char * video = (char *)0xB8000;

	char mario[16][24] = {
		{0,0,0,0x44,0x44,0x44,0x44,0x44,0x44,0,0,0,0},
		{0,0,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0},
		{0,0,0x66,0x66,0x66,0xEE,0xEE,0x66,0xEE,0,0,0},
		{0,0x66,0xEE,0x66,0xEE,0xEE,0xEE,0x66,0xEE,0xEE,0xEE,0},
		{0,0x66,0xEE,0x66,0x66,0xEE,0xEE,0xEE,0x66,0xEE,0xEE,0xEE},
		{0,0x66,0x66,0xEE,0xEE,0xEE,0xEE,0x66,0x66,0x66,0x66,0},
		{0,0,0,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0,0},
		{0,0,0x66,0x66,0x44,0x66,0x66,0x66,0,0,0,0},
		{0,0x66,0x66,0x66,0x44,0x66,0x66,0x44,0x66,0x66,0x66,0},
		{0x66,0x66,0x66,0x66,0x44,0x44,0x44,0x44,0x66,0x66,0x66,0x66},
		{0xEE,0xEE,0x66,0x44,0xEE,0x44,0x44,0xEE,0x44,0x66,0xEE,0xEE},
		{0xEE,0xEE,0xEE,0x44,0x44,0x44,0x44,0x44,0x44,0xEE,0xEE,0xEE},
		{0xEE,0xEE,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xEE,0xEE},
		{0,0,0x44,0x44,0x44,0,0,0x44,0x44,0x44,0,0},
		{0,0x66,0x66,0x66,0,0,0,0,0x66,0x66,0x66,0},
		{0x66,0x66,0x66,0x66,0x88,0x88,0x88,0x88,0x66,0x66,0x66,0x66}} ;

	
	int i, j, k = 0;

	for(i = 0 ; i < COLS*ROWS ; i++)		//dibuja fondo
	{
		video[i*2] = ' ';
		video[i*2 + 1] = 0;
	}

	for(i = 0 ; i < COLS*3 ; i++)			//dibuja piso
	{
		video[3520 + i*2] = ' ';
		video[3520 + i*2 + 1] = 0x88;	
	}
			
	if(mario_vuelve == 0)					//mario va
	{
		k = (mario_timer++)/4;				//(18.2)/4 veces por segundo
		if(k == 68)								
			mario_vuelve = 1;
		for(i=0;i<16;i++)					
			for(j=0;j<12;j++)
				{
					video[1120+i*160+(j*2)+2*k] = ' ';
					video[1120+i*160+(j*2)+2*k+1] = mario[i][j];
				} 
	}
	if(mario_vuelve == 1)					//mario vuelve
	{
		k = (mario_timer--)/4;
		if(k == 0)								
			mario_vuelve = 0;
		for(i=0;i<16;i++)		
			for(j=0;j<12;j++)
			{
				video[1120+i*160+((11-j)*2)+2*k] = ' ';
				video[1120+i*160+((11-j)*2)+2*k+1] = mario[i][j];
			} 
	}
					
}

