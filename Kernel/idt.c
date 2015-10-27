#include <teclado.h>
#include <idt.h>
#include <lib.h>
#include <video.h>
#include <screensaver.h>
#include <RTCkernelspace.h>

int timertick = 0;

void setup_idt()
{
   idt_entry * idt;
   idt = 0;

   idt_set_entry(idt, 0x21, (unsigned long)&int_21_hand , 0x08, 0x8E);
   idt_set_entry(idt, 0x20, (unsigned long)&int_20_hand , 0x08, 0x8E);
   idt_set_entry(idt, 0x80, (unsigned long)&int_80_hand , 0x08, 0x8E);
  
   mascaraPIC1(0xFE&0xFD);  //toma teclado y timertick
   mascaraPIC2(0xFF);
   
}

/* setea una entrada de la IDT */
void idt_set_entry(idt_entry * idt_entries, unsigned char index, 
				unsigned long base, unsigned short sel, unsigned char flags)
{
   idt_entries[index].offset_low = base & 0xFFFF;
   idt_entries[index].offset_mid = (base >> 16) & 0xFFFF;
   idt_entries[index].offset_high = (base >> 32) & 0xFFFF;
   idt_entries[index].selector = sel;
   idt_entries[index].always0 = 0;
   idt_entries[index].always0_2 = 0;
   idt_entries[index].flags = flags;
}

/* maneja los interrupts del teclado */
void keyboard_interrupt(unsigned short entrada)
{	
	unsigned char valor;

	if(suppress_screensaver() == SS_WAS_ON)
		return ;

	valor = translate_keyboard_input(entrada);
	
	if(valor != IGNORE)
		to_input_buffer(valor);

	return ;
}

/* maneja los interrupts del PIT */
void timer_interrupt()
{
	screensavertimer();

	timertick = (timertick+1)%2;

	return ;
}

/* sys call 0xA */
void timer_tick(char * str)
{
	*str = timertick;
}

/* maneja los system calls */
void syscall_handler(uint64_t str, uint64_t len, uint64_t syscall)
{

	switch(syscall)
	{
		case 0x3: sys_readKeyboard((char *)str); break;
		case 0x4: sys_displayWrite((char *)str, len); break;
		case 0x5: read_rtc_time((char *) str, len); break;
		case 0x6: set_rtc_time((char *) str, len); break;
		case 0x7: sys_changeColor(len); break;
		case 0x8: clearscreen(); break;
		case 0x9: set_ss_timeout(len); break;
		case 0xA: timer_tick((char *)str); break;
	}
	return ;
}
