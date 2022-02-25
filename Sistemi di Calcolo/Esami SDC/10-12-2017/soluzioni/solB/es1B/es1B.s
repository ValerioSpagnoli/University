# inserire la soluzione qui...

# int minore(short x, short y);

# int confronta(short* a, short* b, unsigned n) { // a <-> esi, b <-> edi
#     short* end = a + n;                         // end <-> ebx
#     while (a < end)
#         if (!minore(*a++, *b++)) return 0;
#     return 1;
# }

.globl confronta

confronta:
    pushl %esi
    pushl %edi
    pushl %ebx
    subl $8, %esp

    movl 24(%esp), %esi         # esi <-> a
    movl 28(%esp), %edi         # edi <-> b
    movl 32(%esp), %ebx
    leal (%esi, %ebx, 2), %ebx  # ebx <-> a + n
L:  cmpl %ebx, %esi             # if (a >= end)
    jae O                       #     goto O
    movw (%esi), %ax            # ax = *a
    movw (%edi), %cx            # cx = *c
    addl $2, %esi               # a++
    addl $2, %edi               # b++
    movswl %ax, %eax            # eax = (int)ax
    movswl %cx, %ecx            # ecx = (int)cx
    movl %eax, (%esp)
    movl %ecx, 4(%esp)
    call minore                 # eax = minore(eax, ecx)
    testl %eax, %eax            # if (eax != 0)
    jnz L                       #     goto L
    xorl %eax, %eax             # return 0
    jmp E
O:  movl $1, %eax               # return 1
E:  addl $8, %esp
    popl %ebx
    popl %edi
    popl %esi
    ret
