#include <string>

#include "VMTranslator.h"

using namespace std;
string moduleName = "Mymodule";
int counter = 0;
/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){
    string result = "";
    if(segment == "constant"){
        // push constant 1:
        // @1
        // D=A
        // @SP
        // A=M
        // M=D
        // @SP
        // M=M+1
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@SP\n";
        result += "A=M\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "M=M+1\n";
    }else if(segment == "local"){
        // push local 1
        // @1
        // D=A
        // @LCL
        // A=M+D
        // D=M
        // @SP
        // A=M
        // M=D
        // @SP
        // M=M+1
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@LCL\n";
        result += "A=M+D\n";
        result += "D=M\n";
        result += "@SP\n";
        result += "A=M\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "M=M+1\n";
    }else if (segment == "argument"){
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@ARG\n";
        result += "A=M+D\n";
        result += "D=M\n";
        result += "@SP\n";
        result += "A=M\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "M=M+1\n";
    }else if(segment == "temp"){
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@5\n";
        result += "A=A+D\n";
        result += "D=M\n";
        result += "@SP\n";
        result += "A=M\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "M=M+1\n";
    }else if(segment == "this"){
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@THIS\n";
        result += "A=M+D\n";
        result += "D=M\n";
        result += "@SP\n";
        result += "A=M\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "M=M+1\n";
    }else if(segment == "that"){
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@THAT\n";
        result += "A=M+D\n";
        result += "D=M\n";
        result += "@SP\n";
        result += "A=M\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "M=M+1\n";
    }else if(segment == "pointer"){
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@3\n";               // in RAM, pointer address starts from 3
        result += "A=A+D\n";
        result += "D=M\n";
        result += "@SP\n";
        result += "A=M\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "M=M+1\n";
    }else{
        // push static 1
        // @17 /*static values are storing from 16-255*/
        // D=M
        // @SP
        // A=M
        // M=D
        // @SP
        // M=M+1
        result += "@" + to_string(offset + 16) + "\n";    // ----------test--------------
        result += "D=M\n";
        result += "@SP\n";
        result += "A=M\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "M=M+1\n";
    }
    return result;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){   
    string result = "";
    if(segment == "local"){
        // @offset
        // D=A
        // @LCL
        // D=M+D
        // @R1     to store a temp address
        // M=D
        // @SP
        // AM=M-1
        // D=M
        // @R1
        // A=M
        // M=D
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@LCL\n";
        result += "D=M+D\n";
        result += "@R13\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "AM=M-1\n";
        result += "D=M\n";
        result += "@R13\n";
        result += "A=M\n";
        result += "M=D\n";
    }else if(segment == "temp"){
        // temp
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@5\n";
        result += "D=A+D\n";
        result += "@R13\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "AM=M-1\n";
        result += "D=M\n";
        result += "@R13\n";
        result += "A=M\n";
        result += "M=D\n";
    }else if(segment == "argument"){
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@ARG\n";
        result += "D=M+D\n";
        result += "@R13\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "AM=M-1\n";
        result += "D=M\n";
        result += "@R13\n";
        result += "A=M\n";
        result += "M=D\n";
    }else if(segment == "this"){
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@THIS\n";
        result += "D=M+D\n";
        result += "@R13\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "AM=M-1\n";
        result += "D=M\n";
        result += "@R13\n";
        result += "A=M\n";
        result += "M=D\n";
    }else if(segment == "that"){
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@THAT\n";
        result += "D=M+D\n";
        result += "@R13\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "AM=M-1\n";
        result += "D=M\n";
        result += "@R13\n";
        result += "A=M\n";
        result += "M=D\n";
    }else if(segment == "pointer"){
        result += "@" + to_string(offset) + "\n";
        result += "D=A\n";
        result += "@3\n";
        result += "D=A+D\n";
        result += "@R13\n";
        result += "M=D\n";
        result += "@SP\n";
        result += "AM=M-1\n";
        result += "D=M\n";
        result += "@R13\n";
        result += "A=M\n";
        result += "M=D\n";
    }else{
        // @SP
        // AM=M-1
        // D=M
        // @offset+16
        // M=D
        result += "@SP\n";
        result += "AM=M-1\n";
        result += "D=M\n";
        result += "@" + to_string(offset + 16) + "\n";
        result += "M=D\n";
    }
    return result;
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    string result = "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";                  // first element
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "M=D+M\n";                 // second element + first element
    result += "@SP\n";
    result += "M=M+1\n";
    return result;
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    string result = "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";                  // first element
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "M=M-D\n";                 // second element + first element
    result += "@SP\n";
    result += "M=M+1\n";
    return result;
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    string result = "";
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "M=-M\n";
    result += "@SP\n";
    result += "M=M+1\n";
    return result;
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    string result = "";
    // push argument 1
    // push argument 2
    // eq

    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";
    result += "A=A-1\n";
    result += "D=M-D\n";

    result += "@EQTRUE_" + to_string(counter) + "\n";
    result += "D;JEQ\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=0\n";
    result += "@EQEND_" + to_string(counter) + "\n";
    result += "0;JMP\n";
    result += "(EQTRUE_" +to_string(counter) + ")\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=-1\n";
    result += "(EQEND_"+ to_string(counter) + ")\n";
    
    counter++;  // remove repeat label
    return result;
}

/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    string result = "";

    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";
    result += "A=A-1\n";
    result += "D=M-D\n";

    result += "@GTTRUE_"+ to_string(counter) + "\n";
    result += "D;JGT\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=0\n";
    result += "@GTEND_"+ to_string(counter)+ "\n";
    result += "0;JMP\n";
    result += "(GTTRUE_"+ to_string(counter)+ ")\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=-1\n";
    result += "(GTEND_"+ to_string(counter)+ ")\n";
    counter++;
    return result;
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    string result = "";
    result += "@SP\n";
    result += "AM=M-1\n";           // first element 
    result += "D=M\n";
    result += "A=A-1\n";            // second element
    result += "D=M-D\n";

    result += "@LTTRUE_"+ to_string(counter) + "\n";
    result += "D;JLT\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=0\n";
    result += "@LTEND_"+ to_string(counter) + "\n";
    result += "0;JMP\n";
    result += "(LTTRUE_" + to_string(counter) + ")\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=-1\n";
    result += "(LTEND_"+ to_string(counter) + ")\n";
    counter ++;
    return result;
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    string result = "";
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";
    result += "A=A-1\n";
    result += "M=M&D\n";
    return result;
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    string result = "";
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";
    result += "@SP\n";
    result += "A=M-1\n";
    result += "M=D|M\n";
    return result;
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    string result = "";
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "M=!M\n";
    result += "@SP\n";
    result += "M=M+1\n";
    return result;
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    string result = "";
    result += "(" + label + ")" + "\n";
    return result;
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    string result = "";
    result += "@" + label + "\n";
    result += "0;JMP";
    return result;
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    string result = "";
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";
    result += "@" + label +"\n";
    result += "D;JNE\n";
    return result;
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    // Assemble the function label
    string result = "";
    result += "// function\n";
    string functionName = "(" + function_name + ")";
    result += functionName + "\n";
    result += "@SP\n";
    result += "A=M\n";
    
    for(int i = 0; i <n_vars;i++){
        result += "M=0\n";
        result += "A=A+1\n";
    }

    result += "D=A\n";
    result += "@SP\n";
    result += "M=D\n";

    return result;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    // push retAddr01      // saves the return address
    // push LCL            // saves the LCL of f
    // push ARG            // saves the ARG of f
    // push THIS           // saves the THIS of f
    // push THAT            // saves the THAT of f
    // ARG = SP-nArgs-5     // repositions ARG for g
    // LCL = SP             // repositions LCL for g
    // goto g               // transfers control to g
    // (retAddr01)          // the generated label
    
    string result = "";
    string returnSymbol = "RETURN_" + to_string(counter);

    result += "@" + returnSymbol + "\n";
    result += "D=A\n";
    result += "@SP\n";
    result += "A=M\n";
    result += "M=D\n";
    result += "@SP\n";
    result += "M=M+1\n";

    // LCL
    result += "@LCL\n";
    result += "D=M\n";
    result += "@SP\n";
    result += "A=M\n";
    result += "M=D\n";
    result += "@SP\n";
    result += "M=M+1\n";

    // ARG
    result += "@ARG\n";
    result += "D=M\n";
    result += "@SP\n";
    result += "A=M\n";
    result += "M=D\n";
    result += "@SP\n";
    result += "M=M+1\n";

    // THIS
    result += "@THIS\n";
    result += "D=M\n";
    result += "@SP\n";
    result += "A=M\n";
    result += "M=D\n";
    result += "@SP\n";    
    result += "M=M+1\n";

    // THAT
    result += "@THAT\n";
    result += "D=M\n";
    result += "@SP\n";
    result += "A=M\n";
    result += "M=D\n";
    result += "@SP\n";
    result += "M=M+1\n";

    // ARG to SP-n-5
    int new_arg = n_args + 5;
    string new_args_string = to_string(new_arg);
    result += "@" + new_args_string + "\n";
    result += "D=A\n";
    result += "@R13\n";
    result += "M=D\n";
    result += "@SP\n";
    result += "D=M\n";
    result += "@R13\n";
    result += "D=D-M\n";
    result += "@ARG\n";
    result += "M=D\n";

    // LCL to SP
    result += "@SP\n";
    result += "D=M\n";
    result += "@LCL\n";
    result += "M=D\n";

    // goto g
    result += "@"+ function_name+ "\n";
    result += "0;JMP\n";

    result += "(" + returnSymbol + ")\n";
    counter ++;
    result += "// end of call\n";
    return result;
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    // frame = LCL              // frame is a temp. variable
    // retAddr = *(frame-5)     // retAddr is a temp. variable
    // *ARG = pop               // repositions the return value
    // // for the caller
    // SP=ARG+1                 // restores the caller’s SP
    // THAT = *(frame-1)        // restores the caller’s THAT
    // THIS = *(frame-2)        // restores the caller’s THIS
    // ARG = *(frame-3)         // restores the caller’s ARG
    // LCL = *(frame-4)         // restores the caller’s LCL
    // goto retAddr // goto saved returnAddress
    // frame = LCL
    string result = "";
    result += "//retrun!\n";

    result += "@LCL\n";
    result += "D=M\n";
    // frame
    result += "@R13\n";
    result += "M=D\n";

    // retAddr = *(frame-5)
    result += "@5\n";
    result += "A=D-A\n";
    result += "D=M\n";
    // retAddr
    result += "@R14\n";
    result += "M=D\n";

    // *ARG = pop
    result += "@SP\n";
    result += "AM=M-1\n";
    result += "D=M\n";
    result += "@ARG\n";
    result += "A=M\n";
    result += "M=D\n";

    // SP=ARG+1
    result += "@ARG\n";
    result += "D=M+1\n";
    result += "@SP\n";
    result += "M=D\n";

    // that = *(frame -1)
    result += "@R13\n";
    result += "A=M-1\n";
    result += "D=M\n";
    result += "@THAT\n";
    result += "M=D\n";

    // THIS = *(frame -2)
    result += "@R13\n";
    result += "D=M\n";
    result += "@2\n";
    result += "A=D-A\n";
    result += "D=M\n";
    result += "@THIS\n";
    result += "M=D\n";

    // ARG = *(frame-3)
    result += "@R13\n";
    result += "D=M\n";
    result += "@3\n";
    result += "A=D-A\n";
    result += "D=M\n";
    result += "@ARG\n";
    result += "M=D\n";

    // LCL = *(frame-4)
    result += "@R13\n";
    result += "D=M\n";
    result += "@4\n";
    result += "A=D-A\n";
    result += "D=M\n";
    result += "@LCL\n";
    result += "M=D\n";

    result += "@R14\n";
    result += "A=M\n";
    result += "0;JMP\n";

    return result;
}