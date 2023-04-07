// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// R1 contains the RAM address of the first element in the array
@R1
A=M
D=M
// set R0(MIN) == R1
@R0
M=D

@counter                // counter, for traversing the array
M=1

(LOOP)
    @R2                 // D=1-R2
    D=D-M
    @END                // Check if the array is empty, if it is, jump to label end
    D;JEQ

    // Otherwise, continue the loop
    @R0                 
    D=M
    // Check if the current minimum number is less than 0
    @CHECKNEG           
    D;JLT               // If min num < 0, jump
    @CHECKPOS
    D;JGT               // If min num > 0, jump

(CHECKNEG)
    @R1
    D=M

    @counter            // Check if the next number is less than 0 too
    A=D+M
    D=M
    @LOOP2              // If it is, jump
    D;JLT

    @counter            // If not, continue to traversal the array
    M=M+1
    @LOOP
    0;JMP

(CHECKPOS)
    @R1
    D=M

    @counter            // Check if the next number is greater than 0
    A=D+M
    D=M
    @LOOP2              // If it is, jump
    D;JGT

    @R0                 // If it's not, continue the loop
    M=D

    @counter
    M=M+1
    
    @LOOP
    0;JMP

(LOOP2)
    @counter
    D=M
    @R0                 // Check if the current number larger than R0
    D=D-M
    @EXCHANGE           // If the current number < R0, exchange the min number
    D;JLT

    @counter            // If not, continue the loop
    M=M+1
    @LOOP
    0;JMP

(EXCHANGE)
    @R1                 // the RAM address of the first element in the array
    D=M

    @counter            
    A=D+M
    D=M

    @R0                 // Exchange the min value
    M=D

    @counter
    M=M+1

    @LOOP
    0;JMP

(END)