#include "types.h"
#include "vga.h"
#include "io.h"

#define GAR_ADDRESS 0x3CE
u8* video_buffer;

void setPalette(u8 num, RGB_value new) {
	outb(0x3C8, num)
	outb(0x3C9, new.red)
	outb(0x3C9, new.green)
	outb(0x3C9, new.blue)
}

void initDefaultPalette() { // gray-scale
	for (int i=0; i < 25; i++) {
		RGB_value rgb;
		rgb.red = i * 10;
		rgb.green = i * 10;
		rgb.blue = i * 10;
		setPalette(i, rgb);
	}
}

void setVideoMode(u32 mode) {
	int addr = GAR_ADDRESS;
	if (mode == VGA_GRAPHICS_MODE) {
		//print("Flush!!\n");
		
		//inb(0x3DA);
		
		// Select memory map
		//outb(0x3C0, 6)
		//outb(0x03C4, 6)
		//outb(0x03C5, 0b00000001)
		
		// Select graphics mode
		//inb(0x3DA);
		//outb(0x3C0, 5)
		//outb(0x03CE, 5)
		//outb(0x03CF, 0b0100001)
		
		// Other (important to switch mode
		//inb(0x3DA);
		//outb(0x3C0, 2)
		//outb(0x03CE, 2)
		//outb(0x03CF, 0b00001111)
		
		// SEEMS TO WORK (bios interrupts)
		//asm("mov ah, 0");
		//asm("mov al, 12h");
		//asm("int 10h");
		
		// IMPORTANT! Enable CPU write decoding (vsyncp=1, hsyncp=1, clock=01,ram=1,i/oas=1
		//outb(0x03C2, 0b00100011)
		video_buffer = (u8*) 0xA0000;
	} else if (mode == VGA_TEXT_MODE) {
		
	}
}

void plotPixel(u32 x, u32 y, u8 color) {
	video_buffer[y*SCREEN_WIDTH+x] = color;
	//video_buffer[((y<<8)+(y<<6))+x] = color;
	outb(0x3CF, ((y<<8)+(y<<6))+x)
	outb(0x3CF, color);
}