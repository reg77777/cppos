[bits 32]

extern inthandler21

global io_hlt,io_cli,io_sti,io_stihlt
global io_in8
global io_out8
global load_idtr,load_gdtr
global asm_inthandler21

[section .text]

io_hlt:
  hlt
  ret

io_cli:
  cli
  ret

io_sti:
  sti
  ret

io_stihlt:
  sti
  hlt
  ret

io_in8:
  mov edx,[esp+4]
  mov eax,0
  in al,dx
  ret

io_out8:
  mov edx,[esp+4]
  mov al,[esp+8]
  out dx,al
  ret

load_gdtr:
  mov ax,[esp+4]
  mov [esp+6],ax
  lgdt [esp+6]
  ret

load_idtr:
  mov ax,[esp+4]
  mov [esp+6],ax
  lidt [esp+6]
  ret

asm_inthandler21:
  push es
  push ds
  pushad
  mov eax,esp
  push eax
  mov ax,ss
  mov ds,ax
  mov es,ax
  call inthandler21
  pop eax
  popad
  pop ds
  pop es
  iretd
