include Makefile.inc

SAMPLE_DATA=0001-sampleDataModule.bin

all: CodeModule DataModule

CodeModule:
	cd CodeModule; make

DataModule:
	printf "This is sample data." >> $(SAMPLE_DATA) && dd if=/dev/zero bs=1 count=1 >> $(SAMPLE_DATA)

clean:
	cd CodeModule; make clean
	rm -rf *.bin


.PHONY: CodeModule all clean
