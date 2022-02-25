.globl fetch

fetch:
	movl	4(%esp), %eax
	leal	(%eax,%eax,4), %eax
	addl	%eax, %eax
	movl	8(%esp), %edx
	movw	%ax, (%edx)
    movl    $0xABCDDCBA, %eax
    movl    $0xAAAAAAAA, %edx
    movl    $0xCAFEBABE, %ecx
	ret
