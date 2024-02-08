
## FIXED INIT
.print_int:
	.asciz "%d\n" 
.print_str:
	.asciz "%s\n" 
## DATA SECTION
_main:	.long	0
_a:	.long	0
_b:	.long	0
_2:	.long	0
_teeeemp_var_temp0:	.long	0
_3:	.long	0
## TAC_BEGINFUN
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_ADD
	movl _a(%rip), %eax
	movl _b(%rip), %edx
	addl %eax, %edx
	movl %edx, _teeeemp_var_temp0(%rip)

## TAC_ATTR
	movl _teeeemp_var_temp0(%rip), %eax
	movl %eax, _a(%rip)

## TAC_PRINT
	movl	_a(%rip), %esi
	leaq	.print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

## TAC_ENDFUN
	popq	%rbp
	retq
