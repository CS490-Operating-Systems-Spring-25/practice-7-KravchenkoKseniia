.section .data
    buffer: 
        .fill 256, 1, 0
    filename:
        .asciz "task1.txt"
    message:
        .asciz "Hello!\n"

.section .text
  .global _start

_start:
    //get current working directory
    ldr x0, =buffer     //load the buffer
    mov x1, #256
    mov x8, #17         //getcwd
    svc #0

    //print cwd
    mov x0, #1
    ldr x1, =buffer
    mov x2, #256
    mov x8, #64
    svc #0

    // open file in cwd
    mov x0, #-100
    ldr x1, =filename
    mov x2, #0x401
    mov x3, #420
    mov x8, #56
    svc #0

    mov x9, x0 //file descriptor

    //append message
    mov x0, x9
    ldr x1, =message
    mov x2, #7
    mov x8, #64
    svc #0

    //fchmodat
    mov x0, #-100
    ldr x1, =filename
    mov x2, #493        // chmod 755 (rwxr-xr-x)
    mov x3, #0
    mov x8, #53
    svc #0

    //close file
    mov x0, x9
    mov x8, #57
    svc #0

    // Exit
    mov x0, #1         // Exit status
    mov x8, #93        // exit syscall
    svc #0             // Syscall
  