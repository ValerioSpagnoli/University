# inserire la soluzione qui...

# int fetch_elem_ptr(int** p, int* v, int i) { // p <-> eax, v <-> ecx, i <-> edx
#     if (!p) return -1;
#     *p = v + i;
#     return 0;
# }

.globl fetch_elem_ptr

fetch_elem_ptr:
    movl 4(%esp), %eax
    movl 8(%esp), %ecx
    movl 12(%esp), %edx
    testl %eax, %eax
    jz E
    leal (%ecx, %edx, 4), %ecx
    movl %ecx, (%eax)
    xorl %eax, %eax
    ret
E:  movl $-1, %eax
    ret
