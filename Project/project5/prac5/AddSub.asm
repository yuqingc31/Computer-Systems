// Calculates R1 + R2 - R3 and stores the result in R0.
// (R0, R1, R2, R3 refer to RAM[0], RAM[1], RAM[2], and RAM[3], respectively.)

// Put your code here.
// calculate a(R1)+b(R2)-c(R3)
@R1             //a
D=M
@R2             //b
D=D+M           //a+b
@R3
D=D-M           //a + b - c
@R0             //result
M=D