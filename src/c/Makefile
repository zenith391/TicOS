OBJ=kernel
CC=gcc -nostdlib -Wall -fno-pie -m32
BLD=kernel.o screen.o lib.o gdt.o idt.o interrupt.o int.o pic.o vga.o eio.o ata.o

all: $(OBJ) move

kernel: $(BLD)
	ld --oformat binary -melf_i386 -Ttext 1000 $^ -o $@

int.o: int.asm
	nasm -f elf -o $@ $^ 

.o: .c .cpp
	$(CC) $^

clean:
	rm -f $(OBJ) *.o

move:
	mv kernel --target-directory=../../bin
	mv $(BLD) --target-directory=../../bin