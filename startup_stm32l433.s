.syntax unified
.cpu cortex-m4
.thumb

/* Educational excerpt: a real firmware image needs the remaining vectors. */
.section .isr_vector,"a",%progbits
.align 2
.word _estack
.word Reset_Handler

.section .text.Reset_Handler,"ax",%progbits
.global Reset_Handler
.type Reset_Handler, %function
.thumb_func
Reset_Handler:
    /* Copy initialized data from Flash to RAM. */
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata
1:
    cmp r1, r2
    bcs 2f
    ldr r3, [r0], #4
    str r3, [r1], #4
    b 1b

    /* Clear uninitialized data in RAM. */
2:
    ldr r1, =_sbss
    ldr r2, =_ebss
    movs r3, #0
3:
    cmp r1, r2
    bcs 4f
    str r3, [r1], #4
    b 3b

4:
    bl main
5:
    b 5b
.size Reset_Handler, .-Reset_Handler
