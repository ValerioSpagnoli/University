.globl has_duplicates

has_duplicates: # int has_duplicates(short* v, unsigned n)
    # v <-> esi, n <-> edi, i <-> ebx, j <-> ecx, tmp <-> dx, res <-> eax
    # unsigned i,j;
    pushl %esi
    pushl %edi
    pushl %ebx
    movl 16(%esp), %esi
    movl 20(%esp), %edi
    movl $1, %eax           # int res = 1;
    xorl %ebx, %ebx         # i=0;
L1: cmpl %edi, %ebx         # if (i>=n)
    jae E1                  #     goto E1;
    leal 1(%ebx), %ecx      # j=i+1;
L2: cmpl %edi, %ecx         # if (j>=n)
    jae E2                  #     goto E2;
    movw (%esi,%ebx,2), %dx # short tmp = v[i];
    cmpw (%esi,%ecx,2), %dx # if (tmp == v[j])
    je F                    #     goto F;
    incl %ecx               # j++;
    jmp L2                  # goto L2;
E2: incl %ebx               # i++;
    jmp L1                  # goto L1;
E1: xorl %eax, %eax         # res = 0;
F:  popl %ebx
    popl %edi
    popl %esi
    ret
