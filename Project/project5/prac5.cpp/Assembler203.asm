@x
D=M
(LOOP)
    @i
    D=A
    @LOOP
    D;JGT
(WRITE)
    @sum
    D=M
    @LOOP
    D;JLT
(END)
    @END
    0;JMP
    