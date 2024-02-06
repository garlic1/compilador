
	
## TAC_BEGINFUN
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp

	movl	$2, -4(%rbp)
	movl	-4(%rbp), %esi
	leaq	print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

#TAC_ENDFUN
	popq	%rbp
	retq

print_int:
	.asciz	"%d\n"
