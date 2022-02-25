	.file	"es3C.c"
	.text
	.globl	get
	.type	get, @function
get:
.LFB15:
	.cfi_startproc
	movl	8(%esp), %edx
	movl	4(%esp), %eax
	movl	(%eax,%edx,4), %eax
	ret
	.cfi_endproc
.LFE15:
	.size	get, .-get
	.globl	sum_i
	.type	sum_i, @function
sum_i:
.LFB16:
	.cfi_startproc
	movl	4(%esp), %edx
	movl	8(%esp), %ecx
	testl	%edx, %edx
	je	.L5
	movl	$0, %eax
.L4:
	addl	(%edx,%ecx,4), %eax
	movl	8(%edx), %edx
	testl	%edx, %edx
	jne	.L4
	rep ret
.L5:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE16:
	.size	sum_i, .-sum_i
	.globl	sum
	.type	sum, @function
sum:
.LFB17:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	subl	$8, %esp
	.cfi_def_cfa_offset 20
	movl	20(%esp), %ebx
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	sum_i
	movl	%eax, %esi
	movl	$1, 4(%esp)
	movl	%ebx, (%esp)
	call	sum_i
	addl	%esi, %eax
	addl	$8, %esp
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE17:
	.size	sum, .-sum
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
