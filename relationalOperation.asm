null equ 0x00

%macro print_char 1
	mov eax, 4
	mov ebx, 1
	mov ecx, %1
	mov edx, 1
	int 0x80
%endmacro

%macro pushRegisters 0
	push eax
	push ebx
	push ecx
	push edx
%endmacro

%macro popRegisters 0
	pop edx
	pop ecx
	pop ebx
	pop eax
%endmacro

%macro exit0 0
	mov ebx, 0
	mov eax, 1
	int 0x80
%endmacro

section .data
  var1: db 0xff
  var2: db 0xee
  nl: db 0x0a, 0x0d
  msg_EQ: db ' is equal to ', 0x00
  msg_LS: db ' is less than ', 0x00
  msg_GR: db ' is greater than ', 0x00
  msg_prompt1: db 'Please enter a digit: ', 0x00
  msg_prompt2: db 'Please enter a second digit: ', 0x00

section .text
  GLOBAL _start
  _start:
	mov edi, msg_prompt1
	call print_string
	mov eax, 3
	mov ebx, 1
	mov ecx, var1
	mov edx, 1
	int 0x80
	call print_nl
	

	mov edi, msg_prompt2
	call print_string
	mov eax, 3
	mov ebx, 1
	mov ecx, var2
	mov edx, 1
	int 0x80
	call print_nl

	mov eax, 4
	mov ebx, 1
	mov ecx, var1
	mov edx, 1 
	int 0x80

	mov al, [var1]
	cmp al, byte [var2]
	
	je var1_eq_var2
	jg var1_gr_var2
	mov edi, msg_LS
	call print_string
	jmp end_main
	var1_eq_var2:
	  mov edi, msg_EQ
	  call print_string
	  jmp end_main
	var1_gr_var2:
	  mov edi, msg_GR
	  call print_string
	  jmp end_main
	end_main:
	  mov eax, 4
	  mov ebx, 1
	  mov ecx, var2
	  mov edx, 1
	  int 0x80
	  call print_nl
	  exit0

print_nl:
	pushRegisters
	mov eax, 4
	mov ebx, 1
	mov ecx, nl
	mov edx, 2
	int 0x80
	popRegisters
	ret

print_string:
	pushRegisters
	mov ecx, edi
	checknull:
	cmp byte [ecx], null
	jz endstring
	  print_char ecx
	  inc ecx
	  jmp checknull
	endstring:
	popRegisters
	  ret

