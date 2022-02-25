.globl load

load:
    movl 4(%esp), %eax
    movl $10, (%eax)
    movl $0xCAFEBABE, %eax
    movl $0xDEADBABE, %ecx
    movl $0xABADCAFE, %edx
    ret

