c equ 10
org 0x7c00

jmp entry

db 0x90
db "BOOTLOAD"
dw 512
db 1
dw 1
db 2
dw 224
dw 2880
db 0xf0
dw 9
dw 18
dw 2
dd 0
dd 2880 
db 0,0,0x29
dd 0xffffffff     
db "MYSUGOIOS  "
db "FAT12   "     
times 18 db 0

entry:
mov ax,0
mov ss,ax
mov sp,0x7c00
mov ds,ax
mov ax,0x0820
mov es,ax
mov cl,2
mov bx,0
mov dl,0x00

mov ch,0
loop1:
  mov dh,0
  loop2:
    cmp cl,2
    je loop3
      mov cl,1
    loop3:
      mov ah,0x02
      mov al,1
      int 0x13
      mov ax,es
      add ax,0x0020
      mov es,ax
      add cl,1
      cmp cl,18
      jbe loop3
    add dh,1
    cmp dh,2
    jb loop2
  add ch,1
  cmp ch,c
  jb loop1

jmp 0xc200

msg:
	db 0x0a,0x0a
	db "load error"
	db 0x0a
	db 0

times 0x7dfe-0x7c00-($-$$) db 0
db 0x55,0xaa

