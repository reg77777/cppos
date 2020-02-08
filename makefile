BOOTPACK=main.o

head.bin: head.asm
	nasm $^ -o $@

%.o: %.cpp
	g++ -Wall --pedantic-errors -masm=intel -c -m32 -fno-pic -nostdlib -o $*.o $*.cpp

bootloader.bin: bootloader.asm
	nasm $^ -o $@

bootpack.bin: $(BOOTPACK)
	ld -m elf_i386 -e main -Tos.ls $(BOOTPACK) -o $@ 

os.sys: head.bin bootpack.bin
	cat $^ > $@

os.img: bootloader.bin os.sys
	mformat -f 1440 -C -B bootloader.bin -i os.img ::
	mcopy os.sys -i os.img ::

run: os.img
	qemu-system-i386 -m 32M -fda $^
	make clean

clean:
	rm -rf *.sys
	rm -rf *.o
	rm -rf *.img
	rm -rf *.bin
