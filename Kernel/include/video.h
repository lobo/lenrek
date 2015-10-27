#ifndef VIDEO_H
#define VIDEO_H

#define COLS 80
#define ROWS 25

void printchar(const char c);

void scrolldown();

void clearscreen();

void savedisplaystate();

void loaddisplaystate();

void sys_displayWrite(const char * string, unsigned long size);

void sys_changeColor(const char value);

#endif
