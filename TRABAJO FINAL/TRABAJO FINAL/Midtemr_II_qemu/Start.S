    .section .text
    .globl _start

_start:
    # Inicializar stack pointer en la DRAM
    la sp, stack_top

    # Llamar a main()
    call main

    # Si main termina, loop infinito
1:  j 1b

    .section .bss
    .align 4
    .space 4096          # reservar 4KB para la pila
stack_top:

