# inserire la soluzione qui...

# void loads(char**);
# char* get(int i) {
#     char* b;
#     loads(&b);
#     return b + i;
# }

.globl get

get:
    subl $8, %esp
    leal 4(%esp), %eax
    movl %eax, (%esp)
    call loads
    movl 4(%esp), %eax
    addl 12(%esp), %eax
    addl $8, %esp
    ret
