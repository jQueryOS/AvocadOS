; bootloader for jqueryos
; NOTES
; AX - accumlator
; BX - base (address indexing)
; CX - counter (iteration)
; DF - data (w/ AX and large values)

	BITS 16 ; 16-bit mode
	
start:
	mov ax 07C0h ; 0x07C0h is where our bootloader starts

.done:
	dw 0xAA55 ; boot signatre
