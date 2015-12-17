	.globl wrap_2_to_4
wrap_2_to_4:
	push	%ebp
	mov	%esp, %ebp
	push	%edi
	push	%esi
	push	%ebx
	sub	$0x1c, %esp
	mov	8(%ebp), %eax		# struct adaptor *ap
	mov	0xc(%ebp), %edx		# function pointer f
	mov	%edx, -0x1c(%ebp)	# save f in stack slot
	mov	0x10(%ebp), %ecx	# int x
	mov	0x14(%ebp), %edx	# int y

	mov	4(%eax), %esi		# ap->a_val
	testl	%esi, %esi		# ap->a_val == 0
	mov	%edx, %ebx		# %ebx = y
	cmovz	%ecx, %ebx		# %ebx = x
	cmpl	$0, (%eax)		# ap->a_is_const == 0
	cmovnz	%esi, %ebx		# %ebx = ap->a_val
	mov	%ebx, 0x8(%ebp)		# a = %ebx

	mov	12(%eax), %esi		# ap->b_val
	testl	%esi, %esi		# ap->b_val == 0
	mov	%edx, %ebx		# %ebx = y
	cmovz	%ecx, %ebx		# %ebx = x
	cmpl	$0, 8(%eax)		# ap->b_is_const == 0
	cmovnz	%esi, %ebx		# %ebx = ap->b_val
	mov	%ebx, 0xc(%ebp)		# b = %ebx

	mov	20(%eax), %esi		# ap->c_val
	testl	%esi, %esi		# ap->c_val == 0
	mov	%edx, %ebx		# %ebx = y
	cmovz	%ecx, %ebx		# %ebx = x
	cmpl	$0, 16(%eax)		# ap->c_is_const == 0
	cmovnz	%esi, %ebx		# %ebx = ap->c_val
	mov	%ebx, 0x10(%ebp)	# c = %ebx

	mov	28(%eax), %esi		# ap->d_val
	testl	%esi, %esi		# ap->d_val == 0
	mov	%edx, %ebx		# %ebx = y
	cmovz	%ecx, %ebx		# %ebx = x
	cmpl	$0, 24(%eax)		# ap->d_is_const == 0
	cmovnz	%esi, %ebx		# %ebx = ap->d_val
	mov	%ebx, 0x14(%ebp)	# d = %ebx

	mov	-0x1c(%ebp), %edx	# reload f
	add	$0x1c, %esp
	pop	%ebx
	pop	%esi
	pop	%edi
	pop	%ebp
	jmp	*%edx			# tail call (*f)(...)
