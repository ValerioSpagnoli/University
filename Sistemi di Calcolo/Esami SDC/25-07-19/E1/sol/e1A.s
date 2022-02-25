.globl most_freq_char

most_freq_char: # int most_freq_char(const char* s, unsigned* map)
    # s <-> esi, map <-> edi, max <-> eax, i <-> ecx, tmp <-> edx
    pushl %esi
    pushl %edi
    subl $8, %esp
    movl 20(%esp), %esi
    movl 24(%esp), %edi
    # int i;
    movl %edi, (%esp)
    movl $256, 4(%esp)
    call clear                      # clear(map, 256);
    xorl %eax, %eax                 # int max = 0;
L1: movb (%esi), %dl                # ;int tmp = *s;
    movsbl %dl, %edx
    testl %edx, %edx                # if (tmp == 0)
    je E1                           #     goto E1;
    incl (%edi,%edx,4)              # map[tmp]++;
    incl %esi                       # s++;
    jmp L1                          # goto L1;
E1: xorl %ecx, %ecx                 # i=0;
L2: cmpl $256, %ecx                 # if (i>=256)
    jge E2                          #     goto E2;
    movl (%edi,%ecx,4), %edx        # tmp = map[i];
    cmpl (%edi,%eax,4), %edx        # if (tmp > map[max])
    cmovgl %ecx, %eax               # max = i;
    incl %ecx                       # i++;
    jmp L2                          # goto L2;
E2: addl $8, %esp
    popl %edi
    popl %esi
    ret
