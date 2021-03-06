#include "types.h"
#include "io.h"

int ide_common(int drive, int numblock, int count)
{
	outb(0x1F1, 0x00);      /* NULL byte to port 0x1F1 */
	outb(0x1F2, count);     /* Sector count */
	outb(0x1F3, (unsigned char) numblock);  /* Low 8 bits of the block address */
	outb(0x1F4, (unsigned char) (numblock >> 8));   /* Next 8 bits of the block address */
	outb(0x1F5, (unsigned char) (numblock >> 16));  /* Next 8 bits of the block address */

	/* Drive indicator, magic bits, and highest 4 bits of the block address */
	outb(0x1F6, 0xE0 | (drive << 4) | ((numblock >> 24) & 0x0F));

	return 0;
}

int ide_read(int drive, int numblock, int count, char *buf)
{
	u16 tmpword;
	int idx;

	ide_common(drive, numblock, count);
	outb(0x1F7, 0x20);

	/* Wait for the drive to signal that it's ready: */
	while (!(inb(0x1F7) & 0x08));

	for (idx = 0; idx < 256 * count; idx++) {
		tmpword = inw(0x1F0);
		buf[idx * 2] = (unsigned char) tmpword;
		buf[idx * 2 + 1] = (unsigned char) (tmpword >> 8);
	}

	return count;
}

int ide_write(int drive, int numblock, int count, char *buf)
{
	u16 tmpword;
	int idx;

	ide_common(drive, numblock, count);
	outb(0x1F7, 0x30);

	/* Wait for the drive to signal that it's ready: */
	while (!(inb(0x1F7) & 0x08));
	for (idx = 0; idx < 256 * count; idx++) {
		tmpword = (buf[idx * 2 + 1] << 8) | buf[idx * 2];
		outw(0x1F0, tmpword);
	}
	return count;
}