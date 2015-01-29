.data
	number: .quad 6
	buffer: .rept 20
			.ascii " "
			.endr
			
.text
	.globl _start

fib:
	# int fib (int n, int last = 0; int sum = 0)
	#{
	#	return (n == 0) ? 0 : ((n  == 1) ? (sum + 1) : fib(n-1, sum+1, sum+last))
	#}
	# n = %rbx
	# last = %rcx
	# sum = %rax
	
        cmpl $0, %ebx
	je finish
	
	addl $1, %eax          #sum = sum + 1
	cmpl $1, %ebx
	je finish
	
	subl $1, %ebx         #n = n-1
	movl %ecx, %edx       #temp = last
	movl %eax, %ecx		  #last = sum (str.22: sum = sum+1)
	addl %edx, %eax       #sum = sum + last
	subl $1, %eax
	call fib
	
	finish:
	ret
		
number2str:
    movb $0x0a, (%ebx)
    decl %ebx

  write_loop:
    movl $0, %edx
    movl $10, %ecx
    divl %ecx
    addl $0x30, %edx
    movb %dl, (%ebx)
    decl %ebx
    cmpl $0, %eax
    ja   write_loop
    ret	

_start:

	movl number, %ebx	
	movl $0, %eax
	movl $0, %edx
	call fib

	movl $buffer, %ebx
	addl $19, %ebx
    call number2str
	
	# write(1, message, msgend - message);
    movl $4, %eax
    movl $1, %ebx
    movl $buffer, %ecx
    movl $20, %edx
    int $0x80

	#return 0;
    movl $1, %eax
    movl $0, %ebx
    int $0x80
