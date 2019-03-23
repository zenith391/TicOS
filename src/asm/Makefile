OBJ=bootsect 

all: $(OBJ) move

bootsect: boot.asm
	nasm -f bin -o $@ $^ ;

clean:
	rm -f $(OBJ) *.o

move:
	mv bootsect ../../bin/bootsect