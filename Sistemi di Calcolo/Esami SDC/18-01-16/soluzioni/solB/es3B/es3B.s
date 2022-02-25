	.file	"es3B.c"
	.text
	.globl	get
	.type	get, @function
get:
.LFB0:
	.cfi_startproc
	movl	8(%esp), %edx
	movl	4(%esp), %eax
	movl	(%eax,%edx,4), %edx
	movl	12(%esp), %eax
	movsbl	(%edx,%eax), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	get, .-get
	.globl	bazinga
	.type	bazinga, @function
bazinga:
.LFB1:
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
	subl	$8, %esp
	.cfi_def_cfa_offset 28
	movl	32(%esp), %ebp
	testl	%ebp, %ebp
	jle	.L3
	movl	%ebp, 4(%esp)
	movl	28(%esp), %eax
	leal	(%eax,%ebp,4), %eax
	movl	%eax, (%esp)
	movl	$0, %edi
	jmp	.L4
.L5:
	movsbl	(%eax), %ecx
	addl	%ecx, %edx
	addl	$1, %eax
	cmpl	%eax, %ebx
	jne	.L5
	jmp	.L7
.L9:
	movl	$0, %edx
.L7:
	movl	(%esi), %eax
	movb	%dl, (%eax,%edi)
	addl	$4, %esi
	cmpl	%esi, (%esp)
	je	.L6
.L8:
	cmpl	%edi, %ebp
	jle	.L9
	movl	(%esi), %ebx
	leal	(%ebx,%edi), %eax
	addl	4(%esp), %ebx
	movl	$0, %edx
	jmp	.L5
.L6:
	addl	$1, %edi
	cmpl	%edi, %ebp
	je	.L3
.L4:
	movl	28(%esp), %esi
	jmp	.L8
.L3:
	addl	$8, %esp
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
.LFE1:
	.size	bazinga, .-bazinga
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
