GLOBAL set_interrupts
GLOBAL int_21_hand
GLOBAL int_20_hand
GLOBAL int_80_hand
GLOBAL mascaraPIC1,mascaraPIC2
GLOBAL write_byte_to_port_0x70
GLOBAL write_byte_to_port_0x71
GLOBAL read_byte_from_port_0x71
GLOBAL play_sound_asm
GLOBAL stop_sound_asm


extern keyboard_interrupt
extern timer_interrupt
extern syscall_handler

%macro pushaq 0
    push rax      
    push rbx      
    push rcx      
    push rdx      
    push rbp      
    push rdi      
    push rsi      
    push r8       
    push r9       
    push r10      
    push r11      
    push r12      
    push r13      
    push r14      
    push r15      
%endmacro

%macro popaq 0
   	pop r15
   	pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro
	
section .text

int_20_hand:					; Handler de INT 20 ( Timer Tick )
                
	pushaq            			; Se salvan los registros 
	
	call timer_interrupt

	mov al, 20h					; Envio de EOI generico al PIC
	out 20h,al

	popaq

   	iretq
	
int_21_hand:					; Handler de INT 21 ( Teclado )
            
	pushaq           			; Se salvan los registros

	in al, 60h					; Leo el puerto del teclado
	
	mov rdi, rax
	call keyboard_interrupt		

	mov al,20h					; Envio de EOI generico al PIC
	out 20h,al

	popaq

  	iretq

int_80_hand:					; Handler de INT 80 ( llamada al systema )

   	pushaq            			; Se salvan los registros 

	mov rdi, rcx				; Se pasa en rdi el puntero asl buffer
	mov rsi, rdx				; Se pasa en rsi el tamaño del buffer
	mov rdx, rax				; Se pasa en rdx a que syscall se esta llamando
	call syscall_handler

	popaq

   	iretq

set_interrupts:
	sti
	ret

mascaraPIC1:					; Escribe mascara del PIC 1
	push rbp
	mov rbp, rsp   
	mov rax, rdi  
	out 21h, al
	mov rsp,rbp
	pop rbp 
	ret

mascaraPIC2:					; Escribe mascara del PIC 2
	push rbp
	mov rbp, rsp   
	mov rax, rdi  
	out 0A1h, al
	mov rsp,rbp
	pop rbp  
	ret

read_byte_from_port_0x71:		; Se comunica con el RTC
	xor eax, eax
	in al, 0x71
	ret

write_byte_to_port_0x70:		; Se comunica con el RTC
	mov rax, rdi
	out 0x70, al
	ret

write_byte_to_port_0x71:		; Se comunica con el RTC
	mov rax, rdi
	out 0x71, al
	ret

play_sound_asm:

	push rbp
	mov rbp, rsp
	

	mov     al, 182         ; Prepare the speaker for the
	out     43h, al         ;  note.
	mov     ax, di        	; Frequency number (in decimal)
	                        ;  for middle C.
	out     42h, al         ; Output low byte.
	mov     al, ah          ; Output high byte.
	out     42h, al 
	in      al, 61h         ; Turn on note (get value from
	                        ;  port 61h).
	or      al, 00000011b			  ; Set bits 1 and 0.
	out     61h, al         ; Send new value.

	mov rsp,rbp
	pop rbp

	ret

stop_sound_asm:

	push rbp
	mov rbp, rsp

        mov     al, 0   		; Reset bits 1 and 0.
        out     61h, al         ; Send new value.

	mov rsp,rbp
	pop rbp
	ret
