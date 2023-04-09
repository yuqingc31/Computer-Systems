// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// Initialize the product to 0
    @R0
    M=0

    @R1
    D=M
    // Check if R1 < 0. If R1 < 0, jump to LOOP_NEG
    @LOOP2
    D;JLT

//R1>=0
(LOOP)
    @R1
    D=M
    // If R1==0, stop the loop
    @END
    D;JEQ

    @R2
    D=M

    @R1
    M=M-1

    @R0
    M=M+D

    @LOOP
    0;JMP

//R1<0
(LOOP2)
    @R1
    D=M
    // If R1==0, stop the loop
    @END
    D;JEQ

    @R2
    D=M
    @NEG_R2
    D;JLT

    @R1
    M=M+1

    @R0
    M=M-D           

    @LOOP2
    0;JMP

(LOOP3)
    @R1
    D=M
    // If R1==0, stop the loop
    @END
    D;JEQ

    @R2
    D=M
    @NEG_R2
    D;JLT

    @R1
    M=M+1

    @R0
    M=M+D           

    @LOOP3
    0;JMP

(NEG_R2)
    @R2
    D=M
    D=!D
    D=D+1
    @R2
    M=D
    // JMP to R2
    @LOOP3
    0;JMP
    
(END)
