// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)


// Put your code here.

//bubble sort
@i
M=0

(OUTTERLOOP)
	@j
	M=0
    
(INNERLOOP)
	@R1
	D=M
	@j                          // j
	A=M+D
	D=A
	
	@large                      // arr[j+1]
	M=D+1

    @small                      // arr[j]
	M=D
	A=M
	D=M

    @NEG                        // Check if the element is negative
    D;JLT

    @large                      // If not, check the next element
    A=M
    D=M

    @SWAP                       // If it is negative, swap
    D;JLT

    @small
	A=M
	D=M-D                       // j[i] > a[j+1]

	@SWAP
	D;JGT

    @j                          // j++
	M=M+1

	@i
	D=M+1                       // i+1
	@R2
	D=M-D                       // array.length-(i+1)
	@j                      
	D=M-D                       // j-(R2-i-1)

	@INNERLOOP                  // If j-(R2-i-1) < 0, continue the inner loop
	D;JLT

	@i                          // i++
	M=M+1

	@R2
    D=M-1                       // R2-1
    @i
    D=M-D                       // i-(R2-1)

    @OUTTERLOOP                 // If i-(R2-1) < 0 , keep going. if not, end
    D;JLT

    @END
    0;JMP

(SWAP)
    // swap arr[j] -> arr[j+1]
	@small
	A=M
	D=M

	@R3
	M=D

	@large
	A=M
	D=M

	@small
	A=M
	M=D

	@R3
	D=M

	@large
	A=M
	M=D

    @j                          // j++
	M=M+1

	@i
	D=M+1                       // i+1
	@R2
	D=M-D                       // array.length-(i+1)
	@j                      
	D=M-D                       // j-(R2-i-1)

	@INNERLOOP                  // If j-(R2-i-1) < 0, continue the inner loop
	D;JLT

	@i                          // i++
	M=M+1

	@R2
    D=M-1                       // R2-1
    @i
    D=M-D                       // i-(R2-1)

    @OUTTERLOOP                 // If i-(R2-1) < 0 , keep going. if not, end
    D;JLT

    @END
    0;JMP

(NEG)
    @large
    A=M
    D=M

    @EXECUTION                  // If arr[j+1] > 0, j++, i++ 
    D;JGT
    
    @small
	A=M
	D=D-M
	
	@SWAP                       // check if arr[j+1] < arr[j], if it is, swap
	D;JLT

(EXECUTION)
    @j                          // j++
	M=M+1

	@i
	D=M+1                       // i+1
	@R2
	D=M-D                       // array.length-(i+1)
	@j                      
	D=M-D                       // j-(R2-i-1)

	@INNERLOOP                  // If j-(R2-i-1) < 0, continue the inner loop
	D;JLT

	@i                          // i++
	M=M+1

	@R2
    D=M-1                       // R2-1
    @i
    D=M-D                       // i-(R2-1)

    @OUTTERLOOP                 // If i-(R2-1) < 0 , keep going. if not, end
    D;JLT

(END)
    @R0
    M=-1
