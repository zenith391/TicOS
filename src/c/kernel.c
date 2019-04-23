#include "types.h"
#include "gdt.h"
#include "screen.h"
#include "io.h"
#include "idt.h"
#include "vga.h"
#include "events.h"
#include "tasks.h"
#include "pic.h"
#include "ata.h"

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
	printstd("GDT: OK!");
	sti;
	printstd("Interrupts: OK!");
	printstd("TikOS ready! Now the TIC-80 emulator..");
	printerr("TIC-80 emulator not yet implemented!");
	//printstd("Going to VGA graphics mode..");
	show_cursor();
	
	char buf[512];
	char* msg = "Hello World\n";
	memcpy((char*)buf, (char*)msg, 14);
	ide_write(0, 2, 1, buf);
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