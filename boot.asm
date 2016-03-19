; bootloader for jqueryos
; NOTES
; AX - accumlator
; BX - base (address indexing)
; CX - counter (iteration)
; DF - data (w/ AX and large values)

; Switches between 64-bit or 32-bit
%ifdef __x86_64__  
	BITS 64
%else
	BITS 32
%endif
	
start:
	mov eax, 0x07C0 ; 0x07C0h is where our bootloader starts

.done:
	db 0xAA55 ; boot signatre
