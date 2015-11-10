include Makefile.inc

all: DataModule

DataModule:
	cat song >> song.bin && dd if=/dev/zero bs=1 count=1 >> song.bin

clean:
	rm -rf *.bin

