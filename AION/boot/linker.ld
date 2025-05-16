ENTRY(_start)

PHDRS {
    text PT_LOAD FLAGS(5);  /* R-X */
    data PT_LOAD FLAGS(6);  /* RW- */
}

SECTIONS {
    . = 1M;

    .multiboot : {
        *(.multiboot)
    } :text

    .text : {
        *(.text*)
    } :text

    .rodata : {
        *(.rodata*)
    } :text

    .data : {
        *(.data*)
    } :data

    .bss : {
        *(COMMON)
        *(.bss*)
    } :data

    /DISCARD/ : {
        *(.comment)
        *(.note*)
    }
}
