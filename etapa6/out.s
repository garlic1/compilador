
## FIXED INIT
.print_int:
	.asciz "%d\n" 
.print_str:
	.asciz "%s\n" 
.read_int:
	.asciz "%d" 
## TAC_BEGINFUN
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_INPUT
	leaq	.read_int(%rip), %rdi
	leaq	_a(%rip), %rsi
	movb	$0, %al
	callq	__isoc99_scanf@PLT

## TAC_MUL
	movl _a(%rip), %eax
	movl _a(%rip), %edx
	imull %eax, %edx
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
_temp_var_temmmp0:	.long	0
_a:	 .long	0
