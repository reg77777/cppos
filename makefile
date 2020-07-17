BOOTPACK=main.o module/screen.o module/gdt.o module/idt.o module/fifo.o module/func.o #includes/cli.o

run: os.img
	rm -f *.sys
	rm -f *.o
	rm -f *.bin
	rm -f module/*.o
	qemu-system-i386 -m 32M -fda $^
	rm -f *.img

module/func.o: module/func.asm
	nasm -f elf32 $^ -o $@

head.bin: head.asm
	nasm $^ -o $@

bootloader.bin: bootloader.asm
	nasm $^ -o $@

%.o: %.cpp
	g++ -std=c++17 -march=i486 -Wall --pedantic-errors -masm=intel -c -m32 -fno-pic -nostdlib -o $*.o $*.cpp

bootpack.bin: $(BOOTPACK)
	ld -m elf_i386 -e main -Tos.ls $(BOOTPACK) -o $@ 

os.sys: head.bin bootpack.bin
	cat $^ > $@

os.img: bootloader.bin os.sys
	mformat -f 1440 -C -B bootloader.bin -i os.img ::
	mcopy os.sys -i os.img ::

clean:
	rm -f *.sys
	rm -f *.o
	rm -f *.img
	rm -f *.bin
	rm -f module/*.o
