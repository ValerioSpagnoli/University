.globl init_matrix

init_matrix: # void init_matrix(short** m, unsigned n) {
    # m <-> esi, n <-> edi, i <-> ebx, j <-> ebp
    # unsigned i,j;
    pushl %esi
    pushl %edi
    pushl %ebx
    pushl %ebp
    subl $8, %esp
    movl 28(%esp), %esi
    movl 32(%esp), %edi
    xorl %ebx, %ebx             # i=0;
L1: cmpl %edi, %ebx             # if (i>=n)
    jae E1                      #     goto E1;
    xorl %ebp, %ebp             # j=0;
L2: cmpl %edi, %ebp             # if (j>=n)
    jae E2                      #     goto E2;
    movl %ebx, (%esp)
    movl %ebp, 4(%esp)
    call value                  # short tmp = value(i,j);
    movl (%esi,%ebx,4), %ecx    # short* tmp2 = m[i];
    movw %ax, (%ecx,%ebp,2)     # tmp2[j] = tmp;
    incl %ebp                   # j++;
    jmp L2                      # goto L2;
E2: incl %ebx                   # i++;
    jmp L1                      # goto L1;
E1: addl $8, %esp
    popl %ebp
    popl %ebx
    popl %edi
    popl %esi
    ret
