@256
D=A
@0
M=D
@return1
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@LCL
M=D
@ARG
M=D
M=M-1
M=M-1
M=M-1
M=M-1
M=M-1
@Sys.init
0;JEQ
(return1)
(Sys.init)
@4
D=A
@SP
A=M
M=D
@SP
M=M+1
@return2
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@LCL
M=D
@ARG
M=D
M=M-1
M=M-1
M=M-1
M=M-1
M=M-1
M=M-1
@Main.fibonacci
0;JEQ
(return2)
(Sys.init.WHILE)
@Sys.init.WHILE
0;JEQ
(Main.fibonacci)
@0
D=A
@ARG
A=M
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
D=M-D
M=-1
@jump1
D;JLT
@SP
A=M
M=0
(jump1)
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@Main.fibonacci.IF_TRUE
D;JNE
@Main.fibonacci.IF_FALSE
0;JEQ
(Main.fibonacci.IF_TRUE)
@0
D=A
@ARG
A=M
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@R5
M=D
@LCL
A=M
A=A-1
A=A-1
A=A-1
A=A-1
A=A-1
D=M
@R6
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
D=A+1
@SP
M=D
@R5
M=M-1
A=M
D=M
@THAT
M=D
@R5
M=M-1
A=M
D=M
@THIS
M=D
@R5
M=M-1
A=M
D=M
@ARG
M=D
@R5
M=M-1
A=M
D=M
@LCL
M=D
@R6
A=M
0;JEQ
(Main.fibonacci.IF_FALSE)
@0
D=A
@ARG
A=M
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@2
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M-D
@SP
M=M+1
@return3
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@LCL
M=D
@ARG
M=D
M=M-1
M=M-1
M=M-1
M=M-1
M=M-1
M=M-1
@Main.fibonacci
0;JEQ
(return3)
@0
D=A
@ARG
A=M
A=A+D
D=M
@SP
A=M
M=D
@SP
M=M+1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M-D
@SP
M=M+1
@return4
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
D=M
@LCL
M=D
@ARG
M=D
M=M-1
M=M-1
M=M-1
M=M-1
M=M-1
M=M-1
@Main.fibonacci
0;JEQ
(return4)
@SP
M=M-1
A=M
D=M
@SP
M=M-1
A=M
M=M+D
@SP
M=M+1
@LCL
D=M
@R5
M=D
@LCL
A=M
A=A-1
A=A-1
A=A-1
A=A-1
A=A-1
D=M
@R6
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
D=A+1
@SP
M=D
@R5
M=M-1
A=M
D=M
@THAT
M=D
@R5
M=M-1
A=M
D=M
@THIS
M=D
@R5
M=M-1
A=M
D=M
@ARG
M=D
@R5
M=M-1
A=M
D=M
@LCL
M=D
@R6
A=M
0;JEQ
