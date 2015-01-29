.data
 	number: .quad 1
	buffer: .rept 20
			.ascii " "
			.endr
			
.text
	.globl _start
	
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
	#fib2 = 0;
	#if (number == 0)
	#{
		#printf("%d", fib2);
		#return 0;
	#}
	#--number
	
	movl $0, %eax
	movl number, %ebx
	cmpl $0, %ebx
	je       finish 
	
	subl $1, %ebx
	
	#fib2 = 1;
	#fib1 = 0;
	#if (number == 1)
	#{
		#printf("%d", fib2);
		#return 1;
	#}
	
	movl $1, %eax
	cmpl $0, %ebx
	je 	 finish
	
	movl $0, %ecx
	
	#do
	#{
		#tmp = fib2
		#fib2 = fib2 + fib1
		#fib1 = tmp	
		#--number
	#}while(number != 0)
	
	
	loop:
		movl %eax, %edx
		addl %ecx, %eax
		movl %edx, %ecx
		subl $1, %ebx
		cmpl $0, %ebx
		ja 	 loop

	#printf("%d", fib2);

	finish:		
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
