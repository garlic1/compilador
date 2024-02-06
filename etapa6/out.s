
## FIXED INIT
.print_int:
	.asciz "%d\n" 
.print_str:
	.asciz "%s\n" 
## TAC_BEGINFUN
	.globl	funcao
funcao:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_ENDFUN
	popq	%rbp
	retq
