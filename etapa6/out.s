
## FIXED INIT
.print_int:
	.asciz "%d\n" 
.print_str:
	.asciz "%s\n" 
## DATA SECTION
_i:	.long	0
_5:	.long	0
_labelll_newLABEL__0:	.long	0
_labelll_newLABEL__1:	.long	0
_labelll_newLABEL__2:	.long	0
_labelll_newLABEL__3:	.long	0
_labelll_newLABEL__4:	.long	0
_labelll_newLABEL__5:	.long	0
_labelll_newLABEL__6:	.long	0
_"\n":	.long	0
_10:	.long	0
_15:	.long	0
_n:	.long	0
_main:	.long	0
_true:	.long	0
_matrix:	.long	0
_temp_var_temmmp0:	.long	0
_temp_var_temmmp1:	.long	0
_temp_var_temmmp2:	.long	0
_temp_var_temmmp3:	.long	0
_temp_var_temmmp4:	.long	0
_temp_var_temmmp5:	.long	0
_temp_var_temmmp6:	.long	0
_temp_var_temmmp7:	.long	0
_"Digite um numero: \n":	.long	0
_temp_var_temmmp8:	.long	0
_temp_var_temmmp9:	.long	0
_'A':	.long	0
_incn:	.long	0
_'x':	.long	0
_v:	.long	0
_"Nao tem como isso...\n":	.long	0
_x:	.long	0
_100:	.long	0
_'a':	.long	0
_'b':	.long	0
_"OK!\n":	.long	0
_"Dobrando algumas vezes d fica ":	.long	0
_2.5:	.long	0
_a:	.long	0
_b:	.long	0
_c:	.long	0
_55:	.long	0
_d:	.long	0
_0:	.long	0
_1:	.long	0
_f:	.long	0
_2:	.long	0
_number:	.long	0
_"A era=15\n":	.long	0
## TAC_BEGINFUN
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_ATTR
	movl _0(%rip), %eax
	movl %eax, _number(%rip)

## TAC_SUB
	movl _d(%rip), %eax
	movl _i(%rip), %edx
	subl %eax, %edx
	movl %edx, _temp_var_temmmp0(%rip)

## TAC_ATTR
	movl _temp_var_temmmp0(%rip), %eax
	movl %eax, _d(%rip)

## TAC_ATTR
	movl _5(%rip), %eax
	movl %eax, _d(%rip)

## TAC_PRINT
	movl	_temp_var_temmmp1(%rip), %esi
	leaq	.print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

## TAC_PRINT
	movl	_d(%rip), %esi
	leaq	.print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

## TAC_PRINT
	movl	_c(%rip), %esi
	leaq	.print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

## TAC_ATTR
	movl _2(%rip), %eax
	movl %eax, _i(%rip)

## TAC_INPUT
	leaq	.print_int(%rip), %rdi
	leaq	_temp_var_temmmp2(%rip), %rsi
	movb	$0, %al
	callq	__isoc99_scanf@PLT

## TAC_ATTR
	movl _temp_var_temmmp4(%rip), %eax
	movl %eax, _i(%rip)

## TAC_ATTR
	movl _temp_var_temmmp5(%rip), %eax
	movl %eax, _d(%rip)

## TAC_PRINT
	movl	_d(%rip), %esi
	leaq	.print_int(%rip), %rdi
	movb	$0, %al
	callq	printf@PLT

## TAC_ADD
	movl _a(%rip), %eax
	movl _1(%rip), %edx
	addl %eax, %edx
	movl %edx, _temp_var_temmmp7(%rip)

## TAC_ATTR
	movl _temp_var_temmmp7(%rip), %eax
	movl %eax, _a(%rip)

## TAC_ENDFUN
	popq	%rbp
	retq
## TAC_BEGINFUN
	.globl	incn
incn:
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_ADD
	movl _x(%rip), %eax
	movl _n(%rip), %edx
	addl %eax, %edx
	movl %edx, _temp_var_temmmp9(%rip)

## TAC_ENDFUN
	popq	%rbp
	retq
