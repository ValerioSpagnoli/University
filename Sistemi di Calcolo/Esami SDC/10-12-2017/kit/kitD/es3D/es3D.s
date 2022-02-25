	.file	"es3D.c"
	.text
	.globl	charset_new
	.type	charset_new, @function
charset_new:
.LFB15:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	subl	$20, %esp
	.cfi_def_cfa_offset 28
	pushl	$4
	.cfi_def_cfa_offset 32
	call	malloc
	movl	%eax, %ebx
	call	list_new
	movl	%eax, (%ebx)
	movl	%ebx, %eax
	addl	$24, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE15:
	.size	charset_new, .-charset_new
	.globl	charset_add
	.type	charset_add, @function
charset_add:
.LFB16:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	subl	$12, %esp
	.cfi_def_cfa_offset 24
	movl	24(%esp), %ebx
	movzbl	28(%esp), %esi
	pushl	%esi
	.cfi_def_cfa_offset 28
	pushl	(%ebx)
	.cfi_def_cfa_offset 32
	call	list_contains
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	testl	%eax, %eax
	jne	.L3
	subl	$8, %esp
	.cfi_def_cfa_offset 24
	pushl	%esi
	.cfi_def_cfa_offset 28
	pushl	(%ebx)
	.cfi_def_cfa_offset 32
	call	list_add
	addl	$16, %esp
	.cfi_def_cfa_offset 16
.L3:
	addl	$4, %esp
	.cfi_def_cfa_offset 12
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE16:
	.size	charset_add, .-charset_add
	.globl	charset_contains
	.type	charset_contains, @function
charset_contains:
.LFB17:
	.cfi_startproc
	subl	$20, %esp
	.cfi_def_cfa_offset 24
	movzbl	28(%esp), %eax
	pushl	%eax
	.cfi_def_cfa_offset 28
	movl	28(%esp), %eax
	pushl	(%eax)
	.cfi_def_cfa_offset 32
	call	list_contains
	addl	$28, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE17:
	.size	charset_contains, .-charset_contains
	.globl	charset_delete
	.type	charset_delete, @function
charset_delete:
.LFB18:
	.cfi_startproc
	pushl	%ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	subl	$20, %esp
	.cfi_def_cfa_offset 28
	movl	28(%esp), %ebx
	pushl	(%ebx)
	.cfi_def_cfa_offset 32
	call	list_delete
	movl	%ebx, (%esp)
	call	free
	addl	$24, %esp
	.cfi_def_cfa_offset 8
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE18:
	.size	charset_delete, .-charset_delete
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
