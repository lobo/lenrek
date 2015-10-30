#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#define ON 1
#define OFF 0
#define SS_WAS_ON 1
#define SS_IS_OFF 0
#define TICKS_PER_SECOND 18.2

int suppress_screensaver();

void screensavertimer();

void displayscreensaver();

void set_ss_timeout(unsigned long n);

#endif
