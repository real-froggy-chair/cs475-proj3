	.text
	.globl	test_and_set

/**
 * test_and_set: assume it's called with test_and_set(&lock);
 * @param lock pointer to a mutex_t variable
 *
 * TODO - add a comment each line describing its action
 */
test_and_set:
	cli					# Clear interrupt flag
	pushl	%ebx		# preserve contents of the %ebx register, which is about to be modified
	movl	8(%esp), %ebx	# Stack+8 (%esp) is saved in %ebx
	movl	$1, %eax	# %eax is now set to 1
	xchg	%eax, (%ebx)	# Swap %eax and %ebx -- stack + 8 and 1, respectively
	popl	%ebx		# Asking professor. I think this is popping off top of stack into %ebx
	sti					# Set interrupts flag
	ret			# procedure is done ; return
