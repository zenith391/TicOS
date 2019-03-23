#include "types.h"
#include "gdt.h"
#include "scheduler.h"

void schedule(void) {
	u32* stack_ptr;
	u32 esp0, eflags;
	u16 ss, cs;
	
	asm("mov (%%ebp), %%eax; mov %%eax, %0" : "=m" (stack_ptr) : );
	
	
}