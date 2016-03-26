ENTRY(_start)
SECTIONS
{
	. = 1M; /* start */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
	.rodata BLOCK(4K) : ALIGN(4K) /* readonly */
	{
		*(.rodata)
	}
	.data BLOCK(4K) : ALIGN(4K) /* read-write data, inited */
	{
		*(.data)
	}
	.bss BLOCK(4K) : ALIGN(4K) /* Read-write data, uninited; stack */
	{
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
	}
}
