# inserire la soluzione qui...

# int veclen(int x, int y, int* d) { // x <-> eax, y <-> ecx, *d <-> edx
#     return x >= 0 && y >= 0 && x*x+y*y < (*d)*(*d);
# }

.globl veclen

veclen:
    movl 4(%esp),  %eax
    movl 8(%esp),  %ecx
    movl 12(%esp), %edx
    movl (%edx), %edx
    testl %eax, %eax
    jl Z
    testl %ecx, %ecx
    jl Z
    imull %eax, %eax
    imull %ecx, %ecx
    imull %edx, %edx
    addl %ecx, %eax
    cmpl %edx, %eax
    setl %al
    movzbl %al, %eax
    ret
Z:  xorl %eax, %eax
    ret
