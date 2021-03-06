#include <sound.h>
#include <stdint.h>

char* songdir = (char*) 0x500000;

/*Notas validas para ser tocadas*/
uint32_t validnotes[28] = {SILENCE, C6, B5, A5S, A5, G5S, G5, F5S, F5, E5, D5S, D5, 
			C5S, C5, B4, A4S, A4, G4S, G4, F4S, F4, E4, D4S, D4, C4S, C4, A3, G3S}; 

extern uint64_t play_sound_asm(uint32_t freq);

extern uint64_t stop_sound_asm();

float sound_timer = 0;

uint32_t soundstatus = OFF;

float s_timeout = 0;

uint32_t playingsong = OFF;

uint32_t lastsongindex = 0;

/*Tecla para parar el sonido sin importar nada*/
uint32_t Z = OFF;

/*Pone el timer en 0 y activa el sonido*/
void play_beep(uint32_t freq, uint32_t time)
{	
	sound_timer = 0;
	soundstatus = ON;
	s_timeout = (((float)time)/1000)*TICKS_PER_SECOND;
	if(freq != 0)
		play_sound_asm(freq);
	return;
}

/*Calcula la pot de 10*/
uint32_t pot10(uint32_t exp)
{
	if(exp == 0) return 1;	
	return 10*pot10(exp-1);
}

/*Recorre la cancion y la va reproduciendo mientras la parsea de a poco*/
void play_music()
{
	
	uint32_t done = 0;
	
	uint32_t auxNum[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint32_t indexNum = 0;

	uint32_t freq = 0;
	uint32_t time = 0;

	if(songdir[lastsongindex] == 0){
		playingsong = OFF;
		soundstatus = OFF;
		lastsongindex = 0;
	}else{
		while(!done){
			switch(songdir[lastsongindex]){
				case '-': {lastsongindex++;
					  uint32_t aux = indexNum-1;
					  uint32_t freqindex = 0;
					  for(int i = 0; i <= aux; i++){	
					  	freqindex += auxNum[i]*pot10(indexNum-1);
						indexNum--;	
					  }
					  freq = validnotes[freqindex];
					  break;}

				case ',': {lastsongindex++;
					  int aux2 = indexNum-1;
					  for(int i = 0; i <= aux2; i++){
					  	time += auxNum[i]*pot10(indexNum-1);
						indexNum--;	
					  }
					  done = 1; 	
					  playingsong = ON;
				    	  play_beep(freq, time);
					  break;}

				case 0: {
					int aux3 = indexNum-1;
					for(int i = 0; i <= aux3; i++){
					  	time += auxNum[i]*(pot10(indexNum-1)/10);
						indexNum--;	
					}	
					playingsong = ON;
					done = 1;
				    	play_beep(freq, time);
					break;}
			
				default: {auxNum[indexNum] = songdir[lastsongindex] - '0';
					 if(indexNum < 10){
						indexNum++;
					 } 
					 lastsongindex++;
					 break;}
			}
		}

	}
	return;
}


/*Para el sonido porque ya se acabó el tiempo o alguien tocó la tecla indicada,
 si todavía se estaba reproduciendo una cancion entonces la sigue reproduciendo*/
void stop_sound()
{	
	stop_sound_asm();
	if(playingsong == ON && Z == OFF){
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
		Z = ON;
		stop_sound();
		Z = OFF;
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
