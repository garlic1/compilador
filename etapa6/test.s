	.text
	.file	"test.c"
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	$2, -8(%rbp)
	movl	$3, -12(%rbp)
	movl	-8(%rbp), %eax
	addl	-12(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-8(%rbp), %eax
	subl	-12(%rbp), %eax
	movl	%eax, -16(%rbp)
	movl	-8(%rbp), %eax
	imull	-12(%rbp), %eax
	
	movl	%eax, -16(%rbp)
	movl	-8(%rbp), %eax
	cltd
	idivl	-12(%rbp)
	movl	%eax, -16(%rbp)
	
	
	# a < b
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	setl	%al
	andb	$1, %al
	movzbl	%al, %eax
	movl	%eax, -16(%rbp)
	
	
	# a > b
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	setg	%al
	andb	$1, %al
	movzbl	%al, %eax
	movl	%eax, -16(%rbp)
	
	
	# a <= b
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	setle	%al
	andb	$1, %al
	movzbl	%al, %eax
	movl	%eax, -16(%rbp)
	
	
	# a >= b
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	setge	%al
	andb	$1, %al
	movzbl	%al, %eax
	movl	%eax, -16(%rbp)
	
	
	# a != b
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	setne	%al
	andb	$1, %al
	movzbl	%al, %eax
	movl	%eax, -16(%rbp)
	
	
	# a && b
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	cmpl	$0, -8(%rbp)
	movb	%al, -17(%rbp)                  # 1-byte Spill
	je	.LBB0_2
# %bb.1:
	cmpl	$0, -12(%rbp)
	setne	%al
	movb	%al, -17(%rbp)                  # 1-byte Spill
.LBB0_2:
	movb	-17(%rbp), %al                  # 1-byte Reload
	andb	$1, %al
	movzbl	%al, %eax
	movl	%eax, -16(%rbp)
	
	
	# a || b
	movb	$1, %al
	cmpl	$0, -8(%rbp)
	movb	%al, -18(%rbp)                  # 1-byte Spill
	jne	.LBB0_4
# %bb.3:
	cmpl	$0, -12(%rbp)
	setne	%al
	movb	%al, -18(%rbp)                  # 1-byte Spill
.LBB0_4:
	movb	-18(%rbp), %al                  # 1-byte Reload
	andb	$1, %al
	movzbl	%al, %eax
	movl	%eax, -16(%rbp)
	
	
	# !a
	cmpl	$0, -8(%rbp)
	setne	%al
	xorb	$-1, %al
	andb	$1, %al
	movzbl	%al, %eax
	movl	%eax, -16(%rbp)
	movl	-4(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"hello"
	.size	.L.str, 6

	.ident	"Ubuntu clang version 14.0.0-1ubuntu1.1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym printf
