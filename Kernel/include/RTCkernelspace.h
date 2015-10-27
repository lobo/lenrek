#ifndef RTCKERNELSPACE_H	
#define RTCKERNELSPACE_H

#define RTC_ADDRESS_SELECTOR 0x70
#define RTC_DATA_REGISTER 0x71

#define SEGS	0x00
#define MINS	0x02
#define HRS		0x04
#define DIA		0x07
#define MES		0x08
#define ANIO	0x09

// transmiten strings {segundo, minuto, hora, dia, mes, anio} en formato BCD

void read_rtc_time(char * str, unsigned long len);

void set_rtc_time(char * str, unsigned long len);

#endif
