GCC=gcc
GPP=g++
LD=ld
AR=ar
ASM=nasm

GCCFLAGS=-m64 -fno-exceptions -std=c99 -Wno-implicit-function-declaration -Wno-pointer-sign -Wno-int-to-pointer-cast -Wall -ffreestanding -nostdlib -fno-common -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-builtin-malloc -fno-builtin-free -fno-builtin-realloc
ARFLAGS=rvs
ASMFLAGS=-felf64
