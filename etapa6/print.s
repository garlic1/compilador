

_a: .long 2

## TAC_BEGINFUN
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp

	movl	_a(%rip), %esi
	leaq	print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

#TAC_ENDFUN
	popq	%rbp
	retq

print_int:
	.asciz	"%d\n"
