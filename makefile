BOOTPACK=main.o

head.bin: head.asm
	nasm head.asm -o head.bin

%.o: %.cpp
	g++ -masm=intel -c -m32 -fno-pic -nostdlib -o $*.o $*.cpp

bootloader.bin: bootloader.asm
	nasm bootloader.asm -o bootloader.bin

bootpack.bin: $(BOOTPACK)
	ld -m elf_i386 -e main -o bootpack.bin -Tos.ls $(BOOTPACK)

os.sys: head.bin bootpack.bin
	cat head.bin bootpack.bin > os.sys

os.img: bootloader.bin os.sys
	mformat -f 1440 -C -B bootloader.bin -i os.img ::
	mcopy os.sys -i os.img ::

run: os.img
	qemu-system-i386 -m 32M -fda os.img
	make clean

clean:
	rm -rf *.sys
	rm -rf *.o
	rm -rf *.img
	rm -rf *.bin
