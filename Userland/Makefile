include Makefile.inc

all: CodeModule DataModule

CodeModule:
	cd CodeModule; make

DataModule:
	printf "This is sample data." >> DataModule.bin && dd if=/dev/zero bs=1 count=1 >> DataModule.bin

clean:
	cd CodeModule; make clean
	rm -rf *.bin


.PHONY: CodeModule all clean
