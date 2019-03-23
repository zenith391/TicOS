#include "types.h"
#define SCREEN_WIDTH  (u8)320
#define SCREEN_HEIGHT (u8)200

#define VGA_GRAPHICS_MODE 13
#define VGA_TEXT_MODE 14

void setVideoMode(u32);
void plotPixel(u32, u32, u8);

typedef struct {
	u8 red;
	u8 green;
	u8 blue;
} RGB_value;