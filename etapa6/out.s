
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
	movl _b(%rip), %eax
	movl _c(%rip), %edx
	addl %eax, %edx
	movl %edx, _temp_var_temmmp0(%rip)

## TAC_VARIABLE_ATTRIBUTION
	movl _temp_var_temmmp0(%rip), %eax
	movl %eax, _res(%rip)

## TAC_PRINT_EXPRESSION
	movl	_res(%rip), %esi
	leaq	.print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

## TAC_MUL
	movl _b(%rip), %eax
	movl _c(%rip), %edx
	imull %eax, %edx
	movl %edx, _temp_var_temmmp1(%rip)

## TAC_VARIABLE_ATTRIBUTION
	movl _temp_var_temmmp1(%rip), %eax
	movl %eax, _res(%rip)

## TAC_PRINT_EXPRESSION
	movl	_res(%rip), %esi
	leaq	.print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

## TAC_SUB
	movl _c(%rip), %eax
	movl _b(%rip), %edx
	subl %edx, %eax 
	movl %eax, _temp_var_temmmp2(%rip)

## TAC_VARIABLE_ATTRIBUTION
	movl _temp_var_temmmp2(%rip), %eax
	movl %eax, _res(%rip)

## TAC_PRINT_EXPRESSION
	movl	_res(%rip), %esi
	leaq	.print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

## TAC_MUL
	movl _b(%rip), %eax
	movl _c(%rip), %edx
	imull %eax, %edx
	movl %edx, _temp_var_temmmp3(%rip)

## TAC_SUM
	movl _temp_var_temmmp3(%rip), %eax
	movl _c(%rip), %edx
	addl %eax, %edx
	movl %edx, _temp_var_temmmp4(%rip)

## TAC_DIV
	movl _temp_var_temmmp4(%rip), %eax
	movl _c(%rip), %ecx
	cltd
	idivl %ecx
	movl %eax, _temp_var_temmmp5(%rip)

## TAC_VARIABLE_ATTRIBUTION
	movl _temp_var_temmmp5(%rip), %eax
	movl %eax, _res(%rip)

## TAC_PRINT_EXPRESSION
	movl	_res(%rip), %esi
	leaq	.print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

## TAC_ENDFUN
	popq	%rbp
	retq
## DATA SECTION
.data
_temp_var_temmmp0:	.long	0
_temp_var_temmmp1:	.long	0
_temp_var_temmmp2:	.long	0
_temp_var_temmmp3:	.long	0
_temp_var_temmmp4:	.long	0
_temp_var_temmmp5:	.long	0
_a:	 .long	1
_b:	 .long	2
_c:	 .long	3
_res:	 .long	0
