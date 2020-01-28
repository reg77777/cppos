c equ 10
org 0x7c00

jmp entry

db 0x90
db "HELLOIPL"
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
DD 2880 
DB 0,0,0x29
DD 0xffffffff     
DB "HELLO-OS   "  
DB "FAT12   "     
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

error:
  mov ax,0
  mov ss,ax
  mov sp,0x7c00
  mov ds,ax
  mov es,ax
  mov si,msg
  putloop:
    MOV AL, [SI]	;0x10 Charactor_code
    ADD SI, 1			;0x10 Next_word
    CMP AL, 0
    JE  fin
    MOV AH, 0x0e 	;0x10 (Fixation)
    MOV BX, 15
    INT 0x10
    JMP putloop

fin:
	HLT
	JMP fin

msg:
	DB	0x0a,0x0a
	DB	"load error"
	DB	0x0a
	DB	0

times 0x7dfe-0x7c00-($-$$) db 0
db 0x55,0xaa

