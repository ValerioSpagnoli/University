# unsigned char eq(short * x, short * y);

# int is_reversed(short* a, short* b, unsigned n) {
#     int k;
#     short * pa = a;            // pa <-> esi
#     short * pb = b + n - 1;    // pb <-> edi
#     for (k = 0; k < n; k++)    // k  <-> ebx
#         if (!eq(pa + k, pb - k)) return 0;
#     return 1;
# }

.globl is_reversed

is_reversed:
    pushl %esi
    pushl %edi
    pushl %ebx
    subl $8, %esp
    movl 24(%esp), %esi          #    esi = a;
    movl 28(%esp), %eax          #    eax = b
    movl 32(%esp), %ecx          #    ecx = n
    leal -2(%eax,%ecx,2), %edi   #    edi = b + n - 1;
    xorl %ebx, %ebx              #    ebx = 0;
L:  cmpl 32(%esp), %ebx          # L: if (ebx >= n)
    jae T                        #        goto T
    leal (%esi,%ebx,2), %eax     #    eax = esi + 2*ebx
    movl %ebx, %edx              #    edx = ebx
    negl %edx
    leal (%edi,%edx,2), %ecx     #    ecx = edi - 2*edx
    movl %eax, (%esp)
    movl %ecx, 4(%esp)
    call eq
    testl %eax, %eax             #    if (eq(eax, ecx) == 0)
    jz Z                         #        goto Z
    incl %ebx                    #    ebx++
    jmp L                        #    goto L
Z:  xorl %eax, %eax              # Z: eax = 0
    jmp E                        #    goto E
T:  movl $1, %eax                # T: eax = 1
E:  addl $8, %esp                # E: return eax
    popl %ebx
    popl %edi
    popl %esi
    ret
