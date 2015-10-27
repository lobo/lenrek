#ifndef LIB_H
#define LIB_H

#define BUFFERLENGTH 64

void * memset(void * destiny, int32_t c, uint64_t length);
void write(uint64_t len, void *buffer);
void read(uint64_t len, void *buffer); 

#endif
