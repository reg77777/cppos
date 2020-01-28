bootloader.bin: bootloader.asm
	nasm bootloader.asm -o bootloader.bin

os.sys: os.asm
	nasm os.asm -o os.sys

os.img: bootloader.bin os.sys
	mformat -f 1440 -C -B bootloader.bin -i os.img ::
	mcopy os.sys -i os.img ::

run: os.img
	qemu-system-i386 -fda os.img

clean:
	rm -rf *.sys
	rm -rf *.o
	rm -rf *.img
	rm -rf *.bin
