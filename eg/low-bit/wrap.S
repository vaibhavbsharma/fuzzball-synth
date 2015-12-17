# x64 arg registers: %rdi, %rsi, %rdx, %rcx, %r8, %r9
# Callee-saved:	%rbp, %rbx, %r12, %r13, %r14, %r15

	.globl wrap_2_to_4
wrap_2_to_4:
	mov	%rdi, %rax		# struct adaptor *ap
	mov	%rsi, %r10		# function pointer f
	mov	%edx, %r8d		# int x
	mov	%ecx, %r9d		# int y

	mov	4(%rax), %r11d		# ap->a_val
	testl	%r11d, %r11d		# ap->a_val == 0
	mov	%r9d, %edi		# a = y
	cmovz	%r8d, %edi		# a = x (if ap->a_val == 0)
	cmpl	$0, (%rax)		# ap->a_is_const == 0
	cmovnz	%r11d, %edi		# a = ap->a_val (if is_const)

	mov	12(%rax), %r11d		# ap->b_val
	testl	%r11d, %r11d		# ap->b_val == 0
	mov	%r9d, %esi		# b = y
	cmovz	%r8d, %esi		# b = x (if ap->b_val == 0)
	cmpl	$0, 8(%rax)		# ap->b_is_const == 0
	cmovnz	%r11d, %esi		# b = ap->b_val (if is_const)

	mov	20(%rax), %r11d		# ap->c_val
	testl	%r11d, %r11d		# ap->c_val == 0
	mov	%r9d, %edx		# c = y
	cmovz	%r8d, %edx		# c = x (if ap->c_val == 0)
	cmpl	$0, 16(%rax)		# ap->c_is_const == 0
	cmovnz	%r11d, %edx		# c = ap->c_val (if is_const)

	mov	28(%rax), %r11d		# ap->d_val
	testl	%r11d, %r11d		# ap->d_val == 0
	mov	%r9d, %ecx		# d = y
	cmovz	%r8d, %ecx		# d = x (if ap->d_val == 0)
	cmpl	$0, 24(%rax)		# ap->d_is_const == 0
	cmovnz	%r11d, %ecx		# d = ap->d_val (if is_const)

	jmpq	*%r10			# tail call (*f)(...)
