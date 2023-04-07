// Calculates the absolute value of R1 and stores the result in R0.
// (R0, R1 refer to RAM[0], and RAM[1], respectively.)

// Put your code here.

@R1             // contains the number
D=M
@CHECK          // if the number >= 0, jump
D;JGE

@R1             // case for the number < 0
D=-M
@R0
M=D

(CHECK)           
@R0
M=D