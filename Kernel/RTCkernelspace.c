#include <RTCkernelspace.h>

unsigned char rtc_registers[] = {SEGS, MINS, HRS, DIA, MES, ANIO};

extern int write_byte_to_port_0x70(unsigned char c);
extern int write_byte_to_port_0x71(char c);
extern int read_byte_from_port_0x71();

void read_rtc_time(char * str, unsigned long len)
{
	int i;
	
	for(i = 0 ; i < 6 ; i++ )
	{
		write_byte_to_port_0x70(rtc_registers[i]);
		str[i] = (unsigned char) read_byte_from_port_0x71();
	}

}

void set_rtc_time(char * str, unsigned long len)
{
	int i;

	for( i = 0 ; i < 6 ; i++ )
	{
		write_byte_to_port_0x70(rtc_registers[i]);
		write_byte_to_port_0x71(str[i]);
	}
}
