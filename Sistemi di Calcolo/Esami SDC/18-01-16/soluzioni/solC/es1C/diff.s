.globl  diff
diff:
    movsbl  8(%esp), %eax
    movl    4(%esp), %edx
    subl    %eax, %edx
    movl    %edx, %eax
    movl    $0xABCDEFAB, %ecx
    movl    $0xABCDEFAB, %edx
    ret

