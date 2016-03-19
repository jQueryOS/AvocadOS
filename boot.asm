; bootloader for jqueryos
; NOTES
; AX - accumlator
; BX - base (address indexing)
; CX - counter (iteration)
; DF - data (w/ AX and large values)

; Switches between 64-bit or 32-bit
%ifdef __x86_64__  
	[BITS 64]
%else
	[BITS 32]
%endif

[ORG 0x7C00] ; Location of bootloader
	
; mov al, 'a'
; call printchar

jmp $

; printchar:
;   mov ah, 0x0E ; one char
;   mox bh, 0x00 ; page num
;   mov bl, 0x07 ; color

;    int 0x10 ; interupt video
; ret

times 510 - ($ - $$) db 0 ; calculate length of code, set to zero

dw 0xAA55 ; boot signature
