GLOBAL read
GLOBAL write
GLOBAL read_system_time
GLOBAL set_system_time
GLOBAL change_color
GLOBAL clear_screen
GLOBAL set_ss_timer
GLOBAL timer_tick
GLOBAL play_music_sys
GLOBAL play_beep_sys

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

write:

	push rbp
	mov rbp, rsp
					 ;Se usa la convecion de linux
	mov rax, 0x4 ;Se hace la llamada para escribir
	mov rdx, rdi ;Se pasa por el registro rdx el tamaño del buffer
	mov rcx, rsi ;Se pasa por el registro rcx un puntero al buffer
	int 80h

	mov rsp, rbp
	pop rbp
	ret

read:

	push rbp
	mov rbp, rsp
	 				 ;Se usa la convecion de linux
	mov rax, 0x3 ;Se hace la llamada para leer
	mov rdx, rdi ;Se pasa por el registro rdx el tamaño del buffer
	mov rcx, rsi ;Se pasa por el registro rcx un puntero al buffer
	int 0x80

	mov rsp, rbp
	pop rbp
	ret

read_system_time:

	push rbp
	mov rbp, rsp
	 				 ;Se usa la convecion de linux
	mov rax, 0x5 ;Se hace la llamada para rtc_read
	mov rdx ,rdi ;Se pasa por el registro rdx el tamaño del buffer
	mov rcx, rsi ;Se pasa por el registro rcx un puntero al buffer
	int 0x80

	mov rsp, rbp
	pop rbp
	ret

set_system_time:

	push rbp
	mov rbp, rsp
	 				 ;Se usa la convecion de linux
	mov rax, 0x6 ;Se hace la llamada para rtc_read
	mov rdx ,rdi ;Se pasa por el registro rdx el tamaño del buffer
	mov rcx, rsi ;Se pasa por el registro rcx un puntero al buffer
	int 0x80

	mov rsp, rbp
	pop rbp
	ret

change_color:

	push rbp
	mov rbp, rsp
					 ;Se usa la convecion de linux
	mov rax, 0x7 ;Se hace la llamada al systema para cambiar el color de fondo
	mov rdx, rdi ;Se pasa por el registro rdx los colores
	mov rcx, rsi ;
	int 80h

	mov rsp, rbp
	pop rbp
	ret

clear_screen:

	push rbp
	mov rbp, rsp
					 ;Se usa la convecion de linux
	mov rax, 0x8 ;Se hace la llamada al systema para cambiar limpiar la pantalla
	mov rdx, rdi ;
	mov rcx, rsi ;
	int 80h

	mov rsp, rbp
	pop rbp
	ret

set_ss_timer:

	push rbp
	mov rbp, rsp
					 ;Se usa la convecion de linux
	mov rax, 0x9 ;Se hace la llamada al systema para cambiar el timeout del ss
	mov rdx, rdi ;Se pasa la cantidad de segundos
	mov rcx, rsi ;
	int 80h

	mov rsp, rbp
	pop rbp
	ret

timer_tick:

	push rbp
	mov rbp, rsp
					 ;Se usa la convecion de linux
	mov rax, 0xA ;Se hace la llamada al systema para visualizar el flag del tt
	mov rdx, 1 ;
	mov rcx, rdi ;Se pasa un puntero a variable
	int 80h

	mov rsp, rbp
	pop rbp
	ret

play_music_sys:

	push rbp
	mov rbp, rsp
					 ;Se usa la convecion de linux
	mov rax, 0xB ;Se hace la llamada al systema para hacer ruido
	mov rdx, rsi ;
	mov rcx, rdi ;
	int 80h

	mov rsp, rbp
	pop rbp
	ret

play_beep_sys:

	push rbp
	mov rbp, rsp
					 ;Se usa la convecion de linux
	mov rax, 0xC ;			;Se hace la llamada al systema para hacer ruido
	mov rdx, rsi ;
	mov rcx, rdi ;
	int 80h

	mov rsp, rbp
	pop rbp
	ret
