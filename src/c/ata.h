int ide_common(int drive, int numblock, int count);
int ide_read(int drive, int numblock, int count, char* buf);
int ide_write(int drive, int numblock, int count, char* buf);