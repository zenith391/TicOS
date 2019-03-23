#include "types.h"
#include "gdt.h"
#include "screen.h"
#include "io.h"
#include "idt.h"
#include "vga.h"
#include "events.h"
#include "tasks.h"
#include "pic.h"

int main(void);
void goToVga(void);
void printerr(char*);
void printstd(char*);

void _start(void) {
		scrollup(25);
		
		// Init screen
		kc.attr = DEFAULT_STANDARD_ATTRIBUTE; /* Attribute = 0x<bg><fg> */
		kc.y = 0;
		kc.x = 0;
		
		init_idt();
		println("IDT: OK!");
		init_pic();
		println("PIC: OK!");
		init_gdt();
		println("GDT: OK!");
		
		asm("	movw $0x18, %ax \n \
				movw %ax, %ss \n \
				movl $0x20000, %esp");
		
        main();
}

void printerr(char* str) {
	kc.attr = DEFAULT_ERROR_ATTRIBUTE;
	println(str);
}

void printstd(char* str) {
	kc.attr = DEFAULT_STANDARD_ATTRIBUTE;
	println(str);
}

void task1(void) {
	while(1) {
		//print("a");
	}
	return;
}

int main(void) {
		printstd("EternalOS DMK: GDT loaded!");
        printerr("Some test error message");
		printstd("Allowing Interrupts..");
		sti;
		
		printstd("EternalOS DMK: Booted!");
		
//		printstd("EternalOS: Switching to 256-color VGA..");
		
//		pollEvent();
		
//		goToVga();

		show_cursor();
		/*
		printstd("EternalOS: Initializing basic task..");
		// init tss
		struct tss default_tss;
		default_tss.debug_flag = 0x00;
		default_tss.io_map = 0x00;
		default_tss.esp0 = 0x20000;
		default_tss.ss0 = 0x18;
		init_gdt_desc(0x30000, 0x0, 0xFF, 0x0D, &kgdt[4]);
		init_gdt_desc(0x30000, 0x0, 0xF3, 0x0D, &kgdt[5]);
		init_gdt_desc(0x0, 0x20,    0xF7, 0x0D, &kgdt[6]);
		init_gdt_desc((u32) &default_tss, 0x67, 0xE9, 0x00, &kgdt[7]);
		
		// init tss 2
		
		asm("movw $0x38, %ax\
       ltr %ax");
		asm("movw %%ss, %0 \n \
       movl %%esp, %1" : "=m" (default_tss.ss0), "=m" (default_tss.esp0) : );
		asm("cli\
            push $0x33\
            push $0x30000 \
            pushfl \n \
            popl %%eax \n \
            orl $0x200, %%eax \n \
            and $0xffffbfff, %%eax \n \
            push %%eax \n \
            push $0x23 \n \
            push $0x0 \n \
            movl $0x20000, %0 \n \
            movw $0x2B, %%ax \n \
            movw %%ax, %%ds \n \
            iret" : "=m" (default_tss.esp0) : );
		
		memcpy((char*) 0x30000, &task1, 100);
		*/
		printstd("EternalOS: Booting default task..");
		while (1) { // event loop
			
		}
}

void goToVga(void) {
	setVideoMode(VGA_GRAPHICS_MODE);
//	initDefaultPalette();
	for (int i = 0; i < 300; i++) {
		for (int j = 0; j < 20; j++) {
			plotPixel(i, j, (unsigned char) 210);
		}
	}
}