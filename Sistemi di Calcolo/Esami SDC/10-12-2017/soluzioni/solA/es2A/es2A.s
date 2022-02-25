.globl get

get:
    subl $8, %esp
    leal 4(%esp), %eax
    movl %eax, (%esp)
    call load           # load(&z);
    movl 4(%esp), %ecx  # z <-> ecx
    movl 12(%esp), %edx # x <-> edx
    cmpl %ecx, (%edx)
    setle %al           # c1 = x[0] <= z;
    cmpl 4(%edx), %ecx
    setle %ah           # c2 = z <= x[1];
    andb %ah, %al       # c1 = c1 & c2;
    cmpl $0, (%edx)
    setge %ah           # c2 = x[0] >= 0;
    andb %ah, %al       # c1 = c1 & c2;
    movsbl %al, %eax
    addl $8, %esp
    ret
