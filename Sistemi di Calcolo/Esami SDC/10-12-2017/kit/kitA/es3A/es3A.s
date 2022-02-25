	.file	"es3A.c"
	.text
	.globl	quanti_bisestile
	.type	quanti_bisestile, @function
quanti_bisestile:
.LFB1:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	movzwl	12(%esp), %esi
	movl	$0, %edx
	movl	$0, %eax
.L4:
	movl	$0, %ecx
	testb	$3, %dl
	jne	.L2
	movl	%edx, %ecx
	shrw	$2, %cx
	movzwl	%cx, %ecx
	imull	$5243, %ecx, %ecx
	shrl	$17, %ecx
	leal	(%ecx,%ecx,4), %ecx
	leal	(%ecx,%ecx,4), %ecx
	leal	0(,%ecx,4), %ebx
	movl	$1, %ecx
	cmpw	%bx, %dx
	jne	.L2
	movl	%edx, %ecx
	shrw	$4, %cx
	movzwl	%cx, %ecx
	imull	$2622, %ecx, %ecx
	shrl	$16, %ecx
	leal	(%ecx,%ecx,4), %ecx
	leal	(%ecx,%ecx,4), %ecx
	sall	$4, %ecx
	cmpw	%cx, %dx
	sete	%cl
	movzbl	%cl, %ecx
.L2:
	addl	%ecx, %eax
	addl	$1, %edx
	cmpw	%dx, %si
	jnb	.L4
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE1:
	.size	quanti_bisestile, .-quanti_bisestile
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
