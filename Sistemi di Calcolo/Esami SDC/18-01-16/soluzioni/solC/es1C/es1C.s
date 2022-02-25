# int diff(int x, char y);

# int check(int* a, char* b, unsigned n) {
#     int* pa = a + n - 1;
#     while (pa >= a) {
#         int res = diff(*pa--, *b++);
#         if (res & 8 || res & 128 || res & 2048) return 1;
#     }
#     return 0;
# }

.globl check

check:
    pushl %ebx
    pushl %edi
    pushl %esi
    subl $8, %esp
    movl 24(%esp), %esi  # a <-> eax
    movl 28(%esp), %edi  # b <-> edi
    
    movl 32(%esp), %ebx # pa <-> ebx
    imul $4, %ebx
    subl $4, %ebx
    addl %esi, %ebx
L:
    cmpl %esi, %ebx
    jl END

    movl (%ebx), %eax
    movl %eax, (%esp)
    movsbl (%edi), %eax
    movl %eax, 4(%esp)
    call diff

    movl %eax, %edx
    andl $8, %edx
    setnz %cl
    movl %eax, %edx
    andl $128, %edx
    setnz %ch
    orb %ch, %cl
    movl %eax, %edx
    andl $2048, %edx
    setnz %ch
    orb %ch, %cl
    
    jz F
    movl $1, %eax
    addl $8, %esp
    popl %esi
    popl %edi
    popl %ebx
    ret

F:
    subl $4, %ebx
    incl %edi
    jmp L

END:
    movl $0, %eax
    addl $8, %esp
    popl %esi
    popl %edi
    popl %ebx
    ret

    
