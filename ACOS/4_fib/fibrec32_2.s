.data
	number: .quad 10
  	buffer: .rept 20
		.ascii " "
		.endr
			
.text
	.globl _start

fib:

	#if (n == 0) return 0;
	movl $0, %eax
	cmpl $0, %ebx
	je endfib
	
	#if (n == 1) return 1;
	movl $1, %eax
	cmpl $1, %ebx
	je endfib		
			
	
	#n1 = n
    pushl %ebx
	#n1 = n1-1 (n1 == n-1)
	subl $1, %ebx
	#fib(n-1)
	call fib
	pushl %eax   			
	#n1 = n1-1 (n1 == n-2)
	subl $1, %ebx
	#fib(n-2)
	call fib	
	popl %ecx   			
	#temp = fib(n-1) + fib(n-2)
	addl %ecx, %eax    		
	popl %ebx    			
	
	endfib:
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
	movl $0, %ecx
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
