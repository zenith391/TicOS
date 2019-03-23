OBJ=floppyA 

all: $(OBJ) 

floppyA: bootsect kernel
	cat bin/bootsect bin/kernel /dev/zero | dd of=out/floppyA.flp bs=512 count=2880

bootsect: 
	make -C src/asm

kernel: 
	make -C src/c

clean:
	rm -f $(OBJ) *.o
	make -C src/asm clean
	make -C src/c clean
	rm -f bin/*
	
cleanout:
	rm -f out/*