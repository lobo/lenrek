#include <sound.h>
#include <stdint.h>

extern uint64_t play_sound_asm(uint64_t freq);

extern uint64_t stop_sound_asm();

float sound_timer = 0;

unsigned int soundstatus = OFF;

float s_timeout = 0;

void play_beep(uint64_t freq, uint64_t time)
{	
	float time_float = time;
	soundstatus = ON;
	s_timeout = (time_float)*TICKS_PER_SECOND;
	play_sound_asm(freq);
	return;
}

void play_music()
{	

	soundstatus = ON;
	s_timeout = (10000)*TICKS_PER_SECOND;
	//play_sound_asm(SONG);
	return;
}

void stop_sound()
{	
	stop_sound_asm();
	return;
}

/* resetea el timer a 0. Si el sound se encontraba activado lo desactiva */
int suppress_sound()
{
	sound_timer = 0;
	
	if(soundstatus == ON)
	{
		stop_sound();
		soundstatus = OFF;
		return S_WAS_ON;
	}
	
	return S_IS_OFF;
}

/* aumenta el timer con cada interrupcion del timer tick hasta que alcanza el
   valor s_timeout */
void soundtimer()
{
	if(soundstatus == ON);
		sound_timer++;
		
	if(sound_timer >= s_timeout && soundstatus == ON)
	{
		suppress_sound();
	}	
}
