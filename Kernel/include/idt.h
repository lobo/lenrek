#ifndef IDT_H
#define IDT_H
#include <stdint.h>

typedef struct idt_entry_struct
{
   unsigned short offset_low;           
   unsigned short selector;               
   unsigned char  always0;           
   unsigned char  flags;             
   unsigned short offset_mid;
   unsigned int offset_high;             
   unsigned int always0_2;
} idt_entry;

int htoi(const char *str, int *result);

void idt_set_entry(idt_entry *, unsigned char, unsigned long, 
										unsigned short, unsigned char);
void setup_idt();

void mascaraPIC1 (unsigned char mascara);  /* Escribe mascara de PIC1 */

void mascaraPIC2 (unsigned char mascara);  /* Escribe mascara de PIC2 */

void set_interrupts();

void timer_interrupt();

void keyboard_interrupt(unsigned short);

void syscall_handler(unsigned long, unsigned long, unsigned long);

void int_21_hand();

void int_20_hand();

void int_80_hand();

void timer_tick(char *);

void play_beep_idt(uint64_t freq, uint64_t time);

void play_music_idt();

extern int timertick;

#endif
