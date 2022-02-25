	.globl	eq
eq:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movzwl	(%eax), %edx
	movl	12(%ebp), %eax
	movzwl	(%eax), %eax
	cmpw	%ax, %dx
	sete	%al
	movl 	$0xFFFFFFFF, %ecx
	movl 	$0xAAAAAAAA, %ecx
	popl	%ebp
	ret
