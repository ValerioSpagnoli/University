.globl update

update:             # void update(short* v, unsigned n)
    pushl %ebx
    pushl %edi
    pushl %esi
    subl $4, %esp
    movl 20(%esp), %ebx         # v <-> ebx
    movl 24(%esp), %edi         # n <-> edi
    movl $0, %esi               # i <-> esi
L:  cmpl %edi, %esi             # if (i >= n)
    jge E                       # goto E
    cmpw $0, (%ebx, %esi, 2)    # if (v[i] >= 0)
    jge F                       # goto F
    leal (%ebx, %esi, 2), %eax
    movl %eax, (%esp)
    call assoluto               # assoluto(&v[i]);
F:  incl %esi
    jmp L
E:  addl $4, %esp
    popl %esi
    popl %edi
    popl %ebx
    ret
