.STR:
.string	"bazinga!"
.globl	loads

loads:
	movl	4(%esp), %eax
	movl	$.STR, (%eax)
    movl    $0xDEAFBEEF, %ecx
    movl    $0xDEAFBABE, %edx
	ret
