include ../Makefile.inc

MODULE=CodeModule.bin 
SOURCES=$(wildcard *.c) 
OBJECTS=$(SOURCES:.c=.o) 
ASMSOURCES=$(wildcard *.asm) 
ASMOBJECTS=$(ASMSOURCES:.asm=.o) 
STATICLIBS=

all: $(MODULE)

$(MODULE): $(OBJECTS) $(ASMOBJECTS) $(STATICLIBS) 
	$(LD) $(LDFLAGS) -T CodeModule.ld -o ../$(MODULE) $(OBJECTS) $(ASMOBJECTS) $(STATICLIBS)

%.o: %.c
	 $(GCC) $(GCCFLAGS) -c $< -o $@ 

%.o: %.asm 
	$(ASM) $(ASMFLAGS) $< -o $@

clean: 
	rm -rf *.o

.PHONY: all clean
