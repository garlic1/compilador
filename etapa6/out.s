
## FIXED INIT
.print_int:
	.asciz "%d\n" 
.print_str:
	.asciz "%s\n" 
## TAC_BEGINFUN
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_SUM
	movl _a(%rip), %eax
	movl _b(%rip), %edx
	addl %eax, %edx
	movl %edx, _temp_var_temmmp0(%rip)

## TAC_VARIABLE_ATTRIBUTION
	movl _temp_var_temmmp0(%rip), %eax
	movl %eax, _a(%rip)

## TAC_PRINT_EXPRESSION
	movl	_a(%rip), %esi
	leaq	.print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

## TAC_ENDFUN
	popq	%rbp
	retq
## DATA SECTION
.data
_main:	.long	0
_temp_var_temmmp0:	.long	0
_a:	.long	0
_b:	.long	0
_c:	.long	0
