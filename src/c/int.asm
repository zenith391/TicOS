extern isr_default_int, isr_clock_int, isr_kbd_int
global _asm_default_int, _asm_irq_0, _asm_irq_1

_asm_default_int:
	call isr_default_int
	mov al,0x20
	out 0x20,al
	iret

%macro  SAVE_REGS 0
		pushad
		push ds
		push es
		push fs
		push gs
		push ebx
		mov bx,0x10
		mov ds,bx
		pop ebx
%endmacro

%macro  RESTORE_REGS 0
		pop gs
		pop fs
		pop es
		pop ds
		popad
%endmacro

_asm_irq_0:
	SAVE_REGS
	call isr_clock_int
	mov al,0x20
	out 0x20,al
	RESTORE_REGS
	iret

_asm_irq_1:
	call isr_kbd_int
	mov al,0x20
	out 0x20,al
	iret

