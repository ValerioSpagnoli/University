.globl assoluto

assoluto:
	movl 4(%esp), %eax
	movw (%eax), %dx
	testw %dx, %dx
	jge	L
	negw %dx
	movw %dx, (%eax)
L:  movl $0xCAFEBABE, %eax # tamper with caller-save registers to reveal possible errors
    movl $0xABADCAFE, %ecx
    movl $0xDEADBEEF, %edx
    ret
