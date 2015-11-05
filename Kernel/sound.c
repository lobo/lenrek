#include <sound.h>
#include <stdint.h>

extern uint64_t play_sound_asm();

void play_sound()
{	
	play_sound_asm();

  return;
}
