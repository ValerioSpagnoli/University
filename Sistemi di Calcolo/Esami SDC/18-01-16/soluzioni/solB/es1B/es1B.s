# int prod(short x, char y, int * res);

# int check(short* a, char* b, unsigned n) {
#     short* pa = a + n - 1;
#     while (pa >= a) {
#     int res;
#     prod(*pa--, *b++, &res);
#         if (res == 6) return 1;
#     }
#     return 0;
# }

.globl check

check:
    pushl %ebx
    pushl %edi
    pushl %esi
    subl $16, %esp
    movl 32(%esp), %esi  # a <-> eax
    movl 36(%esp), %edi  # b <-> edi
    
    movl %esi, %ebx     # pa <-> ebx
    addl 40(%esp), %ebx
    addl 40(%esp), %ebx
    subl $2, %ebx
L:
    cmpl %esi, %ebx
    jl END

    movswl (%ebx), %eax
    movl %eax, (%esp)
    movsbl (%edi), %eax
    movl %eax, 4(%esp)
    leal 12(%esp), %eax
    movl %eax, 8(%esp)
    call prod

    cmpl $6, 12(%esp)
    jne F
    movl $1, %eax
    addl $16, %esp
    popl %esi
    popl %edi
    popl %ebx
    ret

F:
    subl $2, %ebx
    incl %edi
    jmp L

END:
    movl $0, %eax
    addl $16, %esp
    popl %esi
    popl %edi
    popl %ebx
    ret
