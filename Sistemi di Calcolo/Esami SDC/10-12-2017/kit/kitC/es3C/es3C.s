	.file	"es3C.c"
	.text
	.globl	contain
	.type	contain, @function
contain:
.LFB0:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	movl	8(%esp), %ebx
	movl	16(%esp), %ecx
	movl	12(%esp), %edx
	movl	$0, %eax
	jmp	.L2
.L4:
	addl	$1, %eax
	cmpl	%ecx, -4(%ebx,%eax,4)
	je	.L5
.L2:
	cmpl	%edx, %eax
	jne	.L4
	movl	$0, %eax
	jmp	.L3
.L5:
	movl	$1, %eax
.L3:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE0:
	.size	contain, .-contain
	.globl	search_max
	.type	search_max, @function
search_max:
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
	subl	$4, %esp
	.cfi_def_cfa_offset 24
	movl	28(%esp), %edi
	movl	32(%esp), %ebp
	movl	36(%esp), %eax
	testl	%eax, %eax
	je	.L11
	movl	%eax, (%esp)
	movl	$-1, %esi
	movl	$0, %ebx
.L10:
	pushl	0(%ebp,%ebx,4)
	.cfi_def_cfa_offset 28
	pushl	%edi
	.cfi_def_cfa_offset 32
	pushl	32(%esp)
	.cfi_def_cfa_offset 36
	call	contain
	addl	$12, %esp
	.cfi_def_cfa_offset 24
	testl	%eax, %eax
	cmovne	%ebx, %esi
	addl	$1, %ebx
	cmpl	(%esp), %ebx
	jne	.L10
	jmp	.L8
.L11:
	movl	$-1, %esi
.L8:
	movl	%esi, %eax
	addl	$4, %esp
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
	.size	search_max, .-search_max
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
