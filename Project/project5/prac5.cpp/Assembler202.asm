(LOOP)
    @i
    D=M
    @LOOP
    0;JMP
(WRITE)
    @sum
    D=M
    @LOOP
    D;JLT
(END)
    @END
    0;JMP
    