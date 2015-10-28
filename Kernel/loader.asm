global loader
extern main
extern initializeKernelBinary

loader:
	call initializeKernelBinary	;Set up the kernel binary,get thet stack address
	mov rsp, rax				;Set up the stack with the returned address
	call main
hang:
	hlt							;halt machine should kernel return
	jmp hang
