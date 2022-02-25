	.file	"es3B.c"
	.text
	.globl	sumRangeSqrt
	.type	sumRangeSqrt, @function
sumRangeSqrt:
.LFB22:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$28, %esp
	.cfi_def_cfa_offset 48
	movl	48(%esp), %edi
	cmpl	52(%esp), %edi
	jge	.L4
	movl	%edi, %ebx
	movl	$0, %esi
	movl	%edi, %ebp
	addl	52(%esp), %ebp
.L3:
	movl	%ebx, %eax
	shrl	$31, %eax
	leal	(%ebx,%eax), %edx
	andl	$1, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	addl	%edi, %eax
	movl	%eax, (%esp)
	call	radice
	addl	%ebp, %eax
	addl	%eax, %esi
	addl	$1, %ebx
	cmpl	%ebx, 52(%esp)
	jg	.L3
	jmp	.L2
.L4:
	movl	$0, %esi
.L2:
	movl	%esi, %eax
	addl	$28, %esp
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE22:
	.size	sumRangeSqrt, .-sumRangeSqrt
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
