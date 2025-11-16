	.file	"main.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"\nmain(int argc, char *argv[]): Error:number of arguments\n\n"
.LC1:
	.string	"-v"
.LC2:
	.string	"--version"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$2, -20(%rbp)
	je	.L2
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$58, %edx
	movl	$1, %esi
	movl	$.LC0, %edi
	call	fwrite
	movl	$1, %eax
	jmp	.L14
.L2:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$.LC1, %esi
	movq	%rax, %rdi
	call	strcmp
	testl	%eax, %eax
	je	.L4
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$.LC2, %esi
	movq	%rax, %rdi
	call	strcmp
	testl	%eax, %eax
	jne	.L5
.L4:
	movl	$0, %eax
	call	print_version
	movl	$0, %edi
	call	exit
.L5:
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	creat_buff
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	testq	%rax, %rax
	jne	.L6
	movl	$1, %edi
	call	exit
.L6:
	movl	$0, %eax
	call	creat_stat
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	testq	%rax, %rax
	jne	.L7
	leaq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free_buff
	movl	$1, %edi
	call	exit
.L7:
	movq	-16(%rbp), %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rcx
	leaq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	cp_file2table
	testl	%eax, %eax
	je	.L8
	leaq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free_buff
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free_stat
	movl	$1, %edi
	call	exit
.L8:
	leaq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free_buff
	testl	%eax, %eax
	je	.L9
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free_stat
	movl	$1, %edi
	call	exit
.L9:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	print_table
	testl	%eax, %eax
	je	.L10
	movl	$1, %edi
	call	exit
.L10:
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	calc_stat
	testl	%eax, %eax
	je	.L11
	movl	$1, %edi
	call	exit
.L11:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	print_stat
	testl	%eax, %eax
	je	.L12
	movl	$1, %edi
	call	exit
.L12:
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free_stat
	testl	%eax, %eax
	je	.L13
	movl	$1, %edi
	call	exit
.L13:
	movl	$0, %eax
.L14:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (GNU) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
