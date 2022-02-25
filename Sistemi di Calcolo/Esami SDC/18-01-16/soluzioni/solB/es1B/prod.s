.globl	prod

prod:
	movswl	4(%esp), %edx
	movsbl	8(%esp), %eax
	imull	%edx, %eax
	movl	12(%esp), %edx
	movl	%eax, (%edx)
	movl $0xCAFEBABE, %eax
    	movl $0xDEADBEEF, %ecx
	movl $0xCAFEBABE, %edx
	ret
