#include <sound.h>
#include <stdint.h>

uint32_t arraySong[44] = {C5, C5, C5, G5, G5, A5, A5, G5, F5, F5, E5, E5, D5, D5, C5,
			F5, F5, E5, E5, D5, D5, C5, F5, F5, E5, E5, D5, D5, C5,
			C5, C5, G5, G5, A5, A5, G5, F5, F5, E5, E5, D5, D5, C5, 0};

float arrayTime[44] = {500, 500, 500, 500, 500, 500, 500, 1000, 500, 500, 500,
			500, 500, 500, 1000, 500, 500, 500, 500, 500, 500,
			1000, 500, 500, 500, 500, 500, 500, 1000, 500, 500,
			500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 500, 1000, 0};

extern uint64_t play_sound_asm(uint32_t freq);

extern uint64_t stop_sound_asm();

float sound_timer = 0;

uint32_t soundstatus = OFF;

float s_timeout = 0;

uint32_t playingsong = OFF;

uint32_t lastsongindex = 0;

uint32_t ENTER = OFF;

void play_beep(uint32_t freq, uint32_t time)
{	
	sound_timer = 0;
	soundstatus = ON;
	s_timeout = (((float)time)/1000)*TICKS_PER_SECOND;
	play_sound_asm(freq);
	return;
}

void play_music()
{			
	if(arraySong[lastsongindex++] != 0){
		playingsong = ON;
		soundstatus = ON;
		sound_timer = 0;
		s_timeout = (((float)arrayTime[lastsongindex])/1000)*TICKS_PER_SECOND;
		play_sound_asm(arraySong[lastsongindex]);
	}
	else{
		playingsong = OFF;
		soundstatus = OFF;
		lastsongindex = 0;
	}
	return;
}

void stop_sound()
{	
	stop_sound_asm();
	if(playingsong == ON && ENTER == OFF){
		play_music();
	}
	else
	{
		sound_timer = 0;
		soundstatus = OFF;
		lastsongindex = 0;
	}
	return;
}

/* resetea el timer a 0. Si el sound se encontraba activado lo desactiva */
int suppress_sound()
{	
	if(soundstatus == ON)
	{
		ENTER = ON;
		stop_sound();
		ENTER = OFF;
		return S_WAS_ON;
	}
	
	return S_IS_OFF;
}

/* aumenta el timer con cada interrupcion del timer tick hasta que alcanza el
   valor s_timeout */
void soundtimer()
{
	if(soundstatus == ON);
	{
		sound_timer++;
	}
		
	if(sound_timer >= s_timeout && soundstatus == ON)
	{
		stop_sound();
	}	
}
