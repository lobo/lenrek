#include <stdint.h>
#ifndef SOUND_H
#define SOUND_H
#define TICKS_PER_SECOND 18.2
#define ON 1
#define OFF 0
#define S_WAS_ON 1
#define S_IS_OFF 0
#define SONG (void*)0x500000

void play_music();

void play_beep(uint64_t str, uint64_t len);

void stop_sound();

int suppress_sound();

void soundtimer();

#endif
