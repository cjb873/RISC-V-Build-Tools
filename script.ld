SECTIONS
{
   . = 0x00000;
   .text : { *(.text) }
   .rodata : { *(.rodata) }
   .data : { *(.data) }
   .sdata : { *(.sdata) }
}
