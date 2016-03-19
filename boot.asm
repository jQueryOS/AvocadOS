; bootloader for jqueryos
; NOTES
; AX - accumlator
; BX - base (address indexing)
; CX - counter (iteration)
; DF - data (w/ AX and large values)

; Switches between 64-bit or 32-bit
%ifdef X64
	BITS 64
%else
	BITS 32
%endif
	
start:
	mov ax 07C0h ; 0x07C0h is where our bootloader starts

.done:
	dw 0xAA55 ; boot signatre
