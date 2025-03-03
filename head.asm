org 0xc200

botpack equ 0x00280000
dskcac  equ 0x00100000
dskcac0 equ 0x00008000

cyls  equ 0x0ff0
leds  equ 0x0ff1
vmode equ 0x0ff2
scrnx equ 0x0ff4
scrny equ 0x0ff6
vram  equ 0x0ff8

graphic_setting:
  mov al,0x13
  mov ah,0x00
  int 0x10
  mov byte[vmode],8
  mov word[scrnx],320
  mov word[scrny],200
  mov dword[vram],0x000a0000

get_keyboard:
  mov ah,0x02
  int 0x16
  mov [leds],al

change_mode:
  stop_interrupt:
    mov al,0xff
    out 0x21,al
    nop
    out 0xa1,al
    cli
  call wait_keyboard
  mov al,0xd1
  out 0x64,al
  call wait_keyboard
  mov al,0xdf
  out 0x60,al
  call wait_keyboard

  lgdt [gdtr0]
  mov eax,cr0
  and eax,0x7fffffff
  or eax,0x00000001
  mov cr0,eax
  jmp pipeline_flush

wait_keyboard:
  in al,0x64
  and al,0x02
  jnz wait_keyboard
  ret


pipeline_flush:
  mov ax,8
  mov ds,ax
  mov es,ax
  mov fs,ax
  mov gs,ax
  mov ss,ax
  mov esi,os
  mov edi,botpack
  mov ecx,512*1024/4
  call memcpy

  mov esi,0x7c00
  mov edi,dskcac
  mov ecx,512/4
  call memcpy

  mov esi,dskcac0+512
  mov edi,dskcac+512
  mov ecx,0
  mov cl,byte[cyls]
  imul ecx,512*18*2/4
  sub ecx,512/4
  call memcpy

  mov ebx,botpack
  mov ecx,[ebx+16]
  add ecx,3
  shr ecx,2
  jz skip
  mov esi,[ebx+20]
  add esi,ebx
  mov edi,[ebx+12]
  call memcpy

skip:
  mov esp,[ebx+12]
  jmp dword 2*8:0x0000001b


memcpy:
  mov eax,[esi]
  add esi,4
  mov [edi],eax
  add edi,4
  sub ecx,1
  jnz memcpy
  ret
  alignb 16,db 0

gdt0:
  times 8 db 0
  dw 0xffff,0x0000,0x9200,0x00cf
  dw 0xffff,0x0000,0x9a28,0x0047
  dw 0

gdtr0:
  dw 8*3-1
  dd gdt0
  alignb 16,db 0

os:
