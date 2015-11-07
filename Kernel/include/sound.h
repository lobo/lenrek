#ifndef SOUND_H
#define SOUND_H
#define TICKS_PER_SECOND 0.0182
#define ON 1
#define OFF 0
#define S_WAS_ON 1
#define S_IS_OFF 0
#include <stdint.h>

void play_sound(uint64_t freq, float time);

void stop_sound();

int suppress_sound();

void soundtimer();

#endif
