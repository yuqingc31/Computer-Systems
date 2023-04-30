#include "Assembler.h"
#include "SymbolTable.h"
#include <bitset>
#include <string>

using namespace std;
bitset<16> binary_number(42);
/**
 * Assembler constructor
 */
Assembler::Assembler() {
    // Your code here
}

/**
 * Assembler destructor
 */
Assembler::~Assembler() {
    // Your code here
}

/**
 * Assembler first pass; populates symbol table with label locations.
 * @param instructions An array of the assembly language instructions.
 * @param symbolTable The symbol table to populate.
 */
void Assembler::buildSymbolTable(SymbolTable* symbolTable, string instructions[], int numOfInst) {
    // Your code here
    int currentLineNumber = 0;
    for (int i = 0; i < numOfInst; i++) {
        string instruction = instructions[i];
        // If the instruction is a label, add it to the symbol table with the current line number
        if (instruction[0] == '(') {
            string label = instruction.substr(1, instruction.length() - 2); // Remove the parentheses
            symbolTable->addSymbol(label, currentLineNumber);
        } else {
            currentLineNumber++;
        }
    }
}

/**
 * Assembler second pass; Translates a set of instructions to machine code.
 * @param instructions An array of the assembly language instructions to be converted to machine code.
 * @param symbolTable The symbol table to reference/update.
 * @return A string containing the generated machine code as lines of 16-bit binary instructions.
 */
string Assembler::generateMachineCode(SymbolTable* symbolTable, string instructions[], int numOfInst) {
    string finalResult = "";
    for(int i = 0; i < numOfInst; i++){
        if(parseInstructionType(instructions[i]) == A_INSTRUCTION){
            string value = parseSymbol(instructions[i]);
            finalResult += "0" + translateSymbol(value,symbolTable) +"\n";
        }else if(parseInstructionType(instructions[i]) == L_INSTRUCTION){
            string label = parseSymbol(instructions[i]);
            finalResult += "0" + translateSymbol(label,symbolTable) + "\n";
        }else{  // C_instruction
            string comp = translateComp(parseInstructionComp(instructions[i]));
            string dest = translateDest(parseInstructionDest(instructions[i]));
            string jmp = translateJump(parseInstructionJump(instructions[i]));
            finalResult += "111" + comp + dest + jmp + "\n";
        }
    }
    return finalResult;
}

/**
 * Parses the type of the provided instruction
 * @param instruction The assembly language representation of an instruction.
 * @return The type of the instruction (A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION, NULL)
 */
Assembler::InstructionType Assembler::parseInstructionType(string instruction) {
    // Your code here:
    if (instruction[0] == '@') {
        return A_INSTRUCTION;
    } else if (instruction[0] == '(') {
        return L_INSTRUCTION;
    } else {
        return C_INSTRUCTION;
    }
}

/**
 * Parses the destination of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The destination of the instruction (A, D, M, AM, AD, MD, AMD, NULL)
 */
Assembler::InstructionDest Assembler::parseInstructionDest(string instruction) {
    // Your code here:
    // dest=comp;jump
    size_t eqPos = instruction.find('=');

    string dest = instruction.substr(0,eqPos);

    if (dest == "M") {
        return M;
    } else if (dest == "D") {
        return D;
    } else if (dest == "MD") {
        return MD;
    } else if (dest == "A") {
        return A;
    } else if (dest == "AM") {
        return AM;
    } else if (dest == "AD") {
        return AD;
    } else if (dest == "AMD") {
        return AMD;
    } else {
        return NULL_DEST;
    }
}

/**
 * Parses the jump condition of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The jump condition for the instruction (JLT, JGT, JEQ, JLE, JGE, JNE, JMP, NULL)
 */
Assembler::InstructionJump Assembler::parseInstructionJump(string instruction) {
    // Your code here:
    // for example if "JLT" appear at the comp field return enum label JLT
    if (instruction.find("JLT") != string::npos) {
        return JLT;
    }
    if(instruction.find("JGT") != string::npos){
        return JGT;
    }
    if(instruction.find("JEQ") != string::npos){
        return JEQ;
    }
    if(instruction.find("JGE") != string::npos){
        return JGE;
    }
    if(instruction.find("JNE") != string::npos){
        return JNE;
    }
    if(instruction.find("JLE") != string::npos){
        return JLE;
    }
    if(instruction.find("JMP") != string::npos){
        return JMP;
    }
    return NULL_JUMP;
}

/**
 * Parses the computation/op-code of the provided C-instruction
 * @param instruction The assembly language representation of a C-instruction.
 * @return The computation/op-code of the instruction (CONST_0, ... ,D_ADD_A , ... , NULL)
 */
Assembler::InstructionComp Assembler::parseInstructionComp(string instruction) {
    // Your code here:
    size_t eqPos = instruction.find('=');
    size_t semicolonPos = instruction.find(';');

    // for example if "0" appear at the comp field return CONST_0
    if (instruction.find("0") != string::npos) {
        return CONST_0;
    }
    
    // the location of comp instruction
    string comp = instruction.substr(eqPos+1,semicolonPos-eqPos-1);
    
    if(comp == "1"){
        return CONST_1; 
    }
    if(comp == "-1"){
        return CONST_NEG_1; 
    }
    if(comp == "D"){
        return VAL_D; 
    }
    if(comp == "A"){
        return VAL_A; 
    }
    if(comp == "M"){
        return VAL_M; 
    }
    if(comp == "!M"){
        return NOT_M; 
    }
    if(comp == "!D"){
        return NOT_D; 
    }
    if(comp == "!A"){
        return NOT_A; 
    }
    if(comp == "-D"){
        return NEG_D; 
    }
    if(comp == "-A"){
        return NEG_A; 
    }
    if(comp == "-M"){
        return NOT_D; 
    }
    if(comp == "D+1"){
        return D_ADD_1; 
    }
    if(comp == "A+1"){
        return A_ADD_1; 
    }
    if(comp == "M+1"){
        return M_ADD_1; 
    }
    if(comp == "D-1"){
        return D_SUB_1; 
    }
    if(comp == "A-1"){
        return A_SUB_1; 
    }
    if(comp == "M-1"){
        return M_SUB_1; 
    }
    if(comp == "D+A"){
        return D_ADD_A; 
    }
    if(comp == "D+M"){
        return D_ADD_M; 
    }
    if(comp == "D-A"){
        return D_SUB_A; 
    }
    if(comp == "D-M"){
        return D_SUB_M; 
    }
    if(comp == "A-D"){
        return A_SUB_D; 
    }
    if(comp == "M-D"){
        return M_SUB_D; 
    }
    if(comp == "D&A"){
        return D_AND_A; 
    }
    if(comp == "D&M"){
        return D_AND_M; 
    }
    if(comp == "D|A"){
        return D_OR_A; 
    }
    if(comp == "D|M"){
        return D_OR_M; 
    }
    return NULL_COMP;
}

/**
 * Parses the symbol of the provided A/L-instruction
 * @param instruction The assembly language representation of a A/L-instruction.
 * @return A string containing either a label name (L-instruction),
 *         a variable name (A-instruction), or a constant integer value (A-instruction)
 */
string Assembler::parseSymbol(string instruction) {
    // Check if it's an A-instruction
    if (instruction[0] == '@') {
        // Return the substring after the @ symbol
        return instruction.substr(1);
    }
    // Check if it's an L-instruction
    else {
        // Return the substring between the parentheses
        return instruction.substr(1, instruction.length() - 2);
    }
}

/**
 * Generates the binary bits of the dest part of a C-instruction
 * @param dest The destination of the instruction
 * @return A string containing the 3 binary dest bits that correspond to the given dest value.
 */
string Assembler::translateDest(InstructionDest dest) {
    // Your code here:
    
    
    if(dest == InstructionDest::A){
        return "100";
    }
    if(dest == InstructionDest::D){
        return "010";
    }
    if(dest == InstructionDest::M){
        return "001";
    }
    if(dest == InstructionDest::MD){
        return "011";
    }
    if(dest == InstructionDest::AM){
        return "101";
    }
    if(dest == InstructionDest::AD){
        return "110";
    }
    if(dest == InstructionDest::AMD){
        return "111";
    }
    return "000";
}

/**
 * Generates the binary bits of the jump part of a C-instruction
 * @param jump The jump condition for the instruction
 * @return A string containing the 3 binary jump bits that correspond to the given jump value.
 */
string Assembler::translateJump(InstructionJump jump) {
    // Your code here:
    
    if(jump == InstructionJump::JGT){
        return "001";
    }
    if(jump == InstructionJump::JEQ){
        return "010";
    }
    if(jump == InstructionJump::JGE){
        return "011";
    }
    if(jump == InstructionJump::JLT){
        return "100";
    }
    if(jump == InstructionJump::JNE){
        return "101";
    }
    if(jump == InstructionJump::JLE){
        return "110";
    }
    if(jump == InstructionJump::JMP){
        return "111";
    }
    return "000";
}

/**
 * Generates the binary bits of the computation/op-code part of a C-instruction
 * @param comp The computation/op-code for the instruction
 * @return A string containing the 7 binary computation/op-code bits that correspond to the given comp value.
 */
string Assembler::translateComp(InstructionComp comp) {
    // Your code here:
    if(comp == InstructionComp::CONST_0){
        return "0101010";
    }
    if(comp == InstructionComp::CONST_1){
        return "011111";
    }
    if(comp == InstructionComp::CONST_NEG_1){
        return "0111010";
    }
    if(comp == InstructionComp::VAL_D){
        return "0001100";
    }
    if(comp == InstructionComp::VAL_A){
        return "0110000";
    }
    if(comp == InstructionComp::NOT_D){
        return "0001101";
    }
    if(comp == InstructionComp::NOT_A){
        return "0110001";
    }
    if(comp == InstructionComp::NEG_D){
        return "0001111";
    }
    if(comp == InstructionComp::NEG_A){
        return "0110011";
    }
    if(comp == InstructionComp::D_ADD_1){
        return "0011111";
    }
    if(comp == InstructionComp::A_ADD_1){
        return "0110111";
    }
    if(comp == InstructionComp::D_ADD_A){
        return "0000010";
    }
    if(comp == InstructionComp::D_SUB_A){
        return "0010011";
    }
    if(comp == InstructionComp::A_SUB_D){
        return "0000111";
    }
    if(comp == InstructionComp::D_AND_A){
        return "0000000";
    }
    if(comp == InstructionComp::D_OR_A){
        return "0010101";
    }
    if(comp == InstructionComp::D_SUB_1){
        return "0001110";
    }
    if(comp == InstructionComp::A_SUB_1){
        return "0110010";
    }
    
    
    if(comp == InstructionComp::VAL_M){
        return "1110000";
    }
    if(comp == InstructionComp::NOT_M){
        return "1110001";
    }
    if(comp == InstructionComp::NEG_M){
        return "1110011";
    }
    if(comp == InstructionComp::M_ADD_1){
        return "1110111";
    }
    if(comp == InstructionComp::M_SUB_1){
        return "1110010";
    }
    if(comp == InstructionComp::D_ADD_M){
        return "1000010";
    }
    if(comp == InstructionComp::D_SUB_M){
        return "1010011";
    }
    if(comp == InstructionComp::M_SUB_D){
        return "1000111";
    }
    if(comp == InstructionComp::D_AND_M){
        return "1000000";
    }
    if(comp == InstructionComp::D_OR_M){
        return "1010101";
    }
    return "0000000";
}

/**
 * Generates the binary bits for an A-instruction, parsing the value, or looking up the symbol name.
 * @param symbol A string containing either a label name, a variable name, or a constant integer value
 * @param symbolTable The symbol table for looking up label/variable names
 * @return A string containing the 15 binary bits that correspond to the given sybmol.
 */
string Assembler::translateSymbol(string symbol, SymbolTable* symbolTable) {
    // Your code here:
    // check if the symbol is number
    if(isdigit(symbol[0])) {
        // convert the number to integer and then binary string
        int value = stoi(symbol);
        return bitset<15>(value).to_string();
    }

    int address = symbolTable->getSymbol(symbol);
    if(address != -1){
        // if the symbol is found in the symbol table
        return bitset<15>(address).to_string();
    }

    return "000000000000000";
}

