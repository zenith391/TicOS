#include "types.h"
#include "io.h"
#define __SCREEN__
#include "screen.h"


/*
 * 'scrollup' scroll the screen (the console mapped in ram) to the up
 * of n lines (from 0 to 25).
 */
void scrollup(unsigned int n)
{
		unsigned char *video, *tmp;

		for (video = (unsigned char *) RAMSCREEN;
			 video < (unsigned char *) SCREENLIM; video += 2) {
				tmp = (unsigned char *) (video + n * 160);

				if (tmp < (unsigned char *) SCREENLIM) {
						*video = *tmp;
						*(video + 1) = *(tmp + 1);
				} else {
						*video = 0;
						*(video + 1) = 0x07;
				}
		}

		kc.y -= n;
		if (kc.y < 0)
				kc.y = 0;
}

void move_cursor (u8 x, u8 y)
{
	u16 c_pos;

	c_pos = y * 80 + x;
	outb(0x3d4, 0x0f);
	outb(0x3d5, (u8) c_pos);
	outb(0x3d4, 0x0e);
	outb(0x3d5, (u8) (c_pos >> 8));
}

void show_cursor (void)
{
	move_cursor(kc.x, kc.y);
}

void putcar(uchar c)
{
		unsigned char *video;
		int i;

		if (c == 10) {			/* CR-NL (\n)*/
				kc.x = 0;
				kc.y++;
		} else if (c == 9) {	/* TAB	 (\t)*/
				kc.x = kc.x + 4 - (kc.x % 4);
		} else if (c == 13) {	/* CR	 (\r)*/
				kc.x = 0;
		} else {				/* autres caracteres */
				video = (unsigned char *) (RAMSCREEN + 2 * kc.x + 160 * kc.y);
				*video = c;
				*(video + 1) = kc.attr;

				kc.x++;
				if (kc.x > 79) {
						kc.x = 0;
						kc.y++;
				}
		}

		if (kc.y > 24)
				scrollup(kc.y - 24);
}

/*
 * 'print' shows to screen, at the current position of the cursor, a string
 * of characters ended by \0
 */
void print(char *string)
{
		while (*string != 0) {	/* while character is different from 0x0 */
				putcar(*string);
				string++;
		}
}

void println(char *string) {
	print(string);
	print("\r\n");
}
