.globl minore

minore:
    movzwl 8(%esp), %eax
    cmpw %ax, 4(%esp)
    setl %al
    movzbl %al, %eax
    movl $0xCAFEBABE, %ecx
    movl $0xDEADBEEF, %edx
    ret
