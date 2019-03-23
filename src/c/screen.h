#include "types.h"

#define DEFAULT_ERROR_ATTRIBUTE 0x04
#define DEFAULT_STANDARD_ATTRIBUTE 0x0F

struct cursor_t {
	int x;
	int y;
	int attr;	/* video attributes of the characters to show */
} cursor_t;

#ifdef __SCREEN__

#define RAMSCREEN 0xB8000	/* start of VGA text page memory */
#define SIZESCREEN 0xFA0	/* 4000, numbers of bytes in a text page */
#define SCREENLIM 0xB8FA0	/* end of VGA text page memory*/

struct cursor_t kc;

#else
extern struct cursor_t kc;

#endif				/* __SCREEN__ */


void scrollup(unsigned int);
void putcar(uchar);
void print(char*);
void println(char*);
void show_cursor(void);
void move_cursor(u8, u8);
