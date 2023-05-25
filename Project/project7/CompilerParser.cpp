#include "CompilerParser.h"
#include "ParseTree.h"
#include "Token.h"
#include <cstddef>
#include <cstring>
#include <string>
#include <unordered_set>
#include <vector>
#include <iostream>

using namespace std;

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokens = tokens;
    currentTokenIterator = this->tokens.begin();
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    if(have("keyword","class")){
        cout << "compileProgram"<< endl; 
        return compileClass();
    }
    else{
        throw ParseException();                     // the program doesn't begin with a class
    }
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */

// class
// keyword class
// identifier Main
// symbol {
// classVarDec
// ...
// see classVarDec below
// symbol }

ParseTree* CompilerParser::compileClass() {
    ParseTree *tree = new ParseTree("class", "");
    if(have("keyword", "class")){
        cout << "compileClass keyword class"<< endl; 
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        next();
    }else{
        throw ParseException();
    }

    if(current()->getType() == "identifier"){
        cout << "compileClass identifier Main"<< endl; 
        tree->addChild(new ParseTree("identifier", current()->getValue()));
        next();
    }else{
        throw ParseException();
    }

    if(have("symbol","{")){
        cout << "compileClass symbol {"<< endl;
        tree->addChild(new ParseTree("symbol", current()->getValue())) ;
        next();

        // identify if it is classVarDec or subroutineDec
        while(have("keyword","static") || have("keyword","field")){
            tree->addChild(compileClassVarDec());
        }

        while(have("keyword","constructor") || have("keyword","function") || have("keyword","method")){
            cout << "compileClass keyword function enter"<< endl;
            tree->addChild(compileSubroutine());
        }

        if(have("symbol","}")){
            cout << "compileClass symbol }"<< endl;
            tree->addChild(new ParseTree("symbol",current()->getValue()));
            next();
        }else{
            throw ParseException();
        }
    }else{
        throw ParseException();
    }
    return tree;
}


/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */

// keyword static/field
// keyword int
// identifier a
// symbol ;

ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree *tree = new ParseTree("classVarDec", "");
    if(have("keyword","static") || have("keyword","field")){
        tree->addChild(new ParseTree("keyword",current()->getValue()));
        next();

        if(current()->getType() == "keyword"){
            tree->addChild(new ParseTree("keyword",current()->getValue()));            // var name
            next();
        }else if (current()->getType() == "identifier") {
            tree->addChild(new ParseTree("identifier", current()->getValue())); // variable type (custom identifier)
            next();
        } else{
            throw ParseException();
        }

        if(current()->getType() == "identifier"){
            while(true){
                tree->addChild(new ParseTree("identifier", current()->getValue()));
                next();
                if(have("symbol",",")){                                                 // check if there is ",", if there is, continue the loop, if not, break
                    tree->addChild(new ParseTree("symbol", current()->getValue()));
                    next();
                }else{
                    break;
                }
            }
        }

        if(have("symbol",";")){
            tree->addChild(new ParseTree("symbol", current()->getValue()));
            next();
        }else{
            throw ParseException();
        }
    }
    return tree;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */

// subroutine
// keyword function
// keyword void
// identifier myFunc
// symbol (
// parameterList
// ...
// (see parameterList below)
// symbol )
// subroutineBody
// ...
// see subroutineBody below

ParseTree* CompilerParser::compileSubroutine() {
    ParseTree *tree = new ParseTree("subroutine", "");

    if(have("keyword","function") || have("keyword", "constructor") || have("keyword", "method")){
        cout << "compileSubroutine keyword function"<< endl;
        tree->addChild(new ParseTree("keyword",current()->getValue()));
        next();
    }else{
        throw ParseException();
    }

    if(current()->getType() == "keyword"){ // void | type
        cout << "compileSubroutine keyword void"<< endl;
        tree->addChild(new ParseTree("keyword",current()->getValue()));
        next();
    }else if (current()->getType() == "identifier") {  // className                                             // function name
        tree->addChild(new ParseTree("identifier", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    // subroutineName
    if(current()->getType() == "identifier"){
        tree->addChild(new ParseTree("identifier", current()->getValue()));
        cout << "compileSubroutine " << " " << current()->getType() << " " << current()->getValue() << endl;
        next();
    }else{
        throw ParseException();
    }

    if(have("symbol","(")){
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        cout << "compileSubroutine " << " " << current()->getType() << " " << current()->getValue() << endl;
        next();

        tree->addChild(compileParameterList());

        if (have("symbol", ")")) {
            tree->addChild(new ParseTree("symbol", current()->getValue())); 
            cout << "compileSubroutine " << " " << current()->getType() << " " << current()->getValue() << endl;
            next();
        }else{
            throw ParseException();
        }
    }else{
        throw ParseException();
    }

    tree->addChild(compileSubroutineBody());
    return tree;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */

// int a, char b

// keyword int
// identifier a
// symbol ,
// keyword char
// identifier b
// 1.1.5 compileParameterList (2/6)
ParseTree* CompilerParser::compileParameterList() {
    ParseTree *tree = new ParseTree("parameterList", "");

    // test2

    while(true){
        if(current()->getType() == "keyword" || current()->getType() == "identifier"){                                      // int char boolean className
            if(current()->getValue() == "char" || current()->getValue() == "int" || current()->getValue() == "boolean"){
                cout << "compileParameterList keyword int" << endl;
                tree->addChild(new ParseTree("keyword", current()->getValue()));
                next();
            }else{
                tree->addChild(new ParseTree("identifier", current()->getValue()));
                next();
            }
        }else{
            break;
        }

        if(current()->getType() == "identifier"){
            tree->addChild(new ParseTree("identifier", current()->getValue()));
            cout << "compileParameterList" <<" "<< current()->getType() << " " << current()->getValue() << endl;
            next();
        }else{
            throw ParseException();
        }

        if(currentTokenIterator == tokens.end()){
            return tree;
        }

        if(have("symbol", ",")){
            cout << "compileParameterList symbol ," << endl;
            tree->addChild(new ParseTree("symbol", current()->getValue()));
            next();
        }else{
            break;                                  // last term, break the loop
        }
    }

    return tree;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */

// { 
//     var int a ;
//     let a = 1 ;
// }
// subroutineBody
// symbol {
// varDec
// ...
// (see varDec below)
// statements
// ...
// (see statements below)
// symbol }
// 1.1.6 compileSubroutineBody (1/3)
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree *tree = new ParseTree("subroutineBody", "");
    if(have("symbol","{")){
        tree->addChild(new ParseTree("symbol",current()->getValue()));
        cout << "compileSubroutineBody " << " " << current()->getType() << " " << current()->getValue() << endl;
        next();

        while(have("keyword","var")){
            tree->addChild(compileVarDec());
            cout << "compileSubroutineBody " << " " << current()->getType() << " " << current()->getValue() << endl;
        }

        tree->addChild(compileStatements());

        if(have("symbol", "}")){
            tree->addChild(new ParseTree("symbol",current()->getValue()));
            cout << "compileSubroutineBody " << " " << current()->getType() << " " << current()->getValue() << endl;
            next();
        }else{
            throw ParseException();
        }
    }else{
        throw ParseException();
    }
    return tree;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */

//var int a ;

// keyword var
// keyword int
// identifier a
// symbol ;

// 1.1.7 compileVarDec (2/3)
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* tree = new ParseTree("varDec", "");
    
    if(have("keyword","var")){                                          // var
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        next();
    }else{
        throw ParseException();
    }

    if(current()->getType() == "keyword"){                              // type
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        next();
    }else if(current()->getType() == "identifier"){
        tree->addChild(new ParseTree("identifier", current()->getValue()));
        next();
    }
    else{
        throw ParseException();
    }

    while(true){
        if(current()->getType() == "identifier"){
            tree->addChild(new ParseTree("identifier", current()->getValue()));
            next();
        }else{
            throw ParseException();
        }

        if(have("symbol",",")){
            tree->addChild(new ParseTree("symbol", current()->getValue()));
            next();
        }else{
            break;
        }
    }
    
    if (have("symbol", ";")) {
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    return tree;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
//1.2.1 compileStatements (0/8)
ParseTree* CompilerParser::compileStatements() {
    ParseTree* tree = new ParseTree("statements", "");

    while(true){
        if(currentTokenIterator == tokens.end()){
            break;
        }
        if(current()->getType() == "keyword"){
            if(current()->getValue() == "let"){
                cout << "compileStatements " << current()->getType() << " " << current()->getValue() << endl;
                tree->addChild(compileLet());
            }
            else if (current()->getValue() == "if") {
                tree->addChild(compileIf());
            } else if (current()->getValue() == "while") {
                tree->addChild(compileWhile());
            } else if (current()->getValue() == "do") {
                tree->addChild(compileDo());
            } else if (current()->getValue() == "return") {
                tree->addChild(compileReturn());
            }else{
                break;
            }
        }else{
            break;
        }
    }
    return tree;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */

//'let' varName('[' expression ']')? '=' expression ';'

ParseTree* CompilerParser::compileLet() {
    ParseTree* tree = new ParseTree("letStatement", "");
    
    if (have("keyword", "let")) {
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        cout << "compileLet " << current()->getType() << " " << current()->getValue() << endl;
        next();
    } else {
        throw ParseException();
    }

    if (current()->getType() == "identifier") {   // varName
        tree->addChild(new ParseTree("identifier", current()->getValue()));
        cout << "compileLet " << current()->getType() << " " << current()->getValue() << endl;
        next();
    } else {
        throw ParseException();
    }

    if (have("symbol", "[")) {
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        cout << "compileLet " << current()->getType() << " " << current()->getValue() << endl;
        next();
        tree->addChild(compileExpression());
        if (have("symbol", "]")) {
            tree->addChild(new ParseTree("symbol", current()->getValue()));
            cout << "compileLet " << current()->getType() << " " << current()->getValue() << endl;
            next();
        } else {
            throw ParseException();
        }
    }

    if (have("symbol", "=")) {
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        cout << "compileLet " << current()->getType() << " " << current()->getValue() << endl;
        next();
    } else {
        throw ParseException();
    }

    tree->addChild(compileExpression());

    if (have("symbol", ";")) {
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        cout << "compileLet " << current()->getType() << " " << current()->getValue() << endl;
        next();
    } else {
        throw ParseException();
    }

    return tree;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
//1.2.3 compileIf (6/8)
// 'if'  '('  expression  ')'  '{'  statements  '}'  ('else'   '{'   statements   '}'  )?
ParseTree* CompilerParser::compileIf() {
    ParseTree* tree = new ParseTree("ifStatement", "");
    if(have("keyword","if")){
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        cout << "compileIf " << current()->getType() << " " << current()->getValue() << endl;
        next();
    }else{
        throw ParseException();
    }

    if (have("symbol", "(")) {
        cout << "compileIf " << current()->getType() << " " << current()->getValue() << endl;
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    tree->addChild(compileExpression());

    if (have("symbol", ")")) {
        cout << "compileIf " << current()->getType() << " " << current()->getValue() << endl;
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    if (have("symbol", "{")) {
        cout << "compileIf " << current()->getType() << " " << current()->getValue() << endl;
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    tree->addChild(compileStatements());

    if (have("symbol", "}")) {
        cout << "compileIf " << current()->getType() << " " << current()->getValue() << endl;
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }
    
    if(currentTokenIterator == tokens.end()){
        return tree;
    }

    // Check for optional "else" part
    if (have("keyword", "else")) {
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        next();

        if (have("symbol", "{")) {
            tree->addChild(new ParseTree("symbol", current()->getValue()));
            next();
        } else {
            throw ParseException();
        }

        tree->addChild(compileStatements());

        if (have("symbol", "}")) {
            tree->addChild(new ParseTree("symbol", current()->getValue()));
            next();
        } else {
            throw ParseException();
        }

        if(currentTokenIterator == tokens.end()){
            return tree;
        }
    }

    return tree;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
//1.2.4 compileWhile (0/8)
// 'while'+'(' + expression + ')' + '{'  + statements + '}' +  ('else'  +  '{' +  statements + '}'  )?
ParseTree* CompilerParser::compileWhile() {
    ParseTree* tree = new ParseTree("whileStatement", "");
    if(have("keyword","while")){
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        cout << "compileWhile " << current()->getType() << " " << current()->getValue() << endl;
        next();
    }else {
        throw ParseException();
    }

    if (have("symbol", "(")) {
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        cout << "compileWhile " << current()->getType() << " " << current()->getValue() << endl;
        next();
    } else {
        throw ParseException();
    }

    tree->addChild(compileExpression());

    if (have("symbol", ")")) {
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        cout << "compileWhile " << current()->getType() << " " << current()->getValue() << endl;
        next();
    } else {
        throw ParseException();
    }

    if (have("symbol", "{")) {
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        cout << "compileWhile " << current()->getType() << " " << current()->getValue() << endl;
        next();
    } else {
        throw ParseException();
    }

    tree->addChild(compileStatements());

    if (have("symbol", "}")) {
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        cout << "compileWhile " << current()->getType() << " " << current()->getValue() << endl;
        next();
    } else {
        throw ParseException();
    }

    if(currentTokenIterator == tokens.end()){
        return tree;
    }
    // check if there is 'else'
    if (have("keyword", "else")) {
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        next();

        if (have("symbol", "{")) {
            tree->addChild(new ParseTree("symbol", current()->getValue()));
            next();
        } else {
            throw ParseException();
        }

        tree->addChild(compileStatements());

        if (have("symbol", "}")) {
            tree->addChild(new ParseTree("symbol", current()->getValue()));
            next();
        } else {
            throw ParseException();
        }
        
        if(currentTokenIterator == tokens.end()){
            return tree;
        }
    }
    return tree;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
// ‘do'+ expression + ';'
ParseTree* CompilerParser::compileDo() {
    ParseTree* tree = new ParseTree("doStatement","");
    if(have("keyword","do")){
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        next();
    }else{
        throw ParseException();
    }

    tree->addChild(compileExpression());

    if(have("symbol",";")){
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        next();
    }else{
        throw ParseException();
    }

    return tree;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* tree = new ParseTree("returnStatement","");
    if(have("keyword","return")){
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        next();
    }else{
        throw ParseException();
    }

    // check if there is a expression
    if (!have("symbol", ";")) {
        tree->addChild(compileExpression());
    }

    if (have("symbol", ";")) {
        tree->addChild(new ParseTree("symbol", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }
    return tree;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
// 'skip'  |  (term(op term)*)
ParseTree* CompilerParser::compileExpression() {
    ParseTree* tree = new ParseTree("expression", "");
    if(have("keyword","skip")){
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        cout << "compileExpression " << current()->getType() << " " << current()->getValue() << endl;
        next();
    }else{
        
        tree->addChild(compileTerm());              // first term

        while(true){
            if(currentTokenIterator == tokens.end()){
                return tree;
            }

            if(current()->getType() == "symbol"){

            if(current()->getValue() == "+" || current()->getValue() == "-" || current()->getValue() == "*" || current()->getValue() == "/" || current()->getValue() == "&" || current()->getValue() == "|" || current()->getValue() == "<" || current()->getValue() == ">" || current()->getValue() == "="){
                tree->addChild(new ParseTree("symbol", current()->getValue()));
                cout << "compileExpression " << current()->getType() << " " << current()->getValue() << endl;
                next();
                tree->addChild(compileTerm());
            }else{
                    break;
                }
            }

        }
    }
    return tree;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */

// For tokens: ( ( a + ( 1 - c ) ) > 5 ) = true 
// integerConstant | stringConstant | keywordConstant | varName | varName + '[' + expression + ']' | '(' + expression + ')' | (unaryOp term) | subroutineCall
ParseTree* CompilerParser::compileTerm() {
    ParseTree* tree = new ParseTree("term", "");
    if(current()->getType() == "integerConstant" || current()->getType() == "stringConstant" || current()->getType() == "keywordConstant"){
        tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
        next();
    }
    else if (current()->getType() == "identifier"){            // varName || routinecall
        // routinecall: subroutineName '(' expressList ')'| className | varName '.' subroutineName '(' expressList ')'
        tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
        next();

        // varName + '[' + expression + ']'
        if(have("symbol","[")){
            tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
            cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
            next();

            tree->addChild(compileTerm());

            if(have("symbol", "]")){
                tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
                cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
                next();
            }else{
                throw ParseException();
            }
        }

        // subroutineName '(' expressList ')'
        if(have("symbol", "(")){                                
            tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
            cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
            next();

            tree->addChild(compileExpressionList());

            if(have("symbol",")")){
                tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
                cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
                next();
            }else{
                throw ParseException();
            }
        }

        if(have("symbol",".")){
            tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
            cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
            next();

            if(current()->getType() == "identifier"){
                tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
                cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
                next();
            }else{
                throw ParseException();
            }

            if(have("symbol", "(")){
                tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
                cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
                next();
            }else{
                throw ParseException();
            }

            tree->addChild(compileExpressionList());

            if(have("symbol", ")")){
                tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
                cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
                next();
            }else{
                throw ParseException();
            }
        }
    }
    else if (have("symbol","(")){
        //'(' + expression + ')' 
        tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
        next();
        
        tree->addChild(compileExpression());

        if(have("symbol", ")")){
            tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
            cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
            next();
        }
    }

    else if(have("symbol","~") || have("symbol", "-")){
        tree->addChild(new ParseTree(current()->getType(), current()->getValue()));
        cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
        next();
    }
    else if(have("keyword","true") || have("keyword","false")){
        tree->addChild(new ParseTree("keyword", current()->getValue()));
        cout << "compileTerm " << current()->getType() << " " << current()->getValue() << endl;
        next();
    }
    else {
        throw ParseException();
    }

    return tree;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    ParseTree* tree = new ParseTree("expressionList", "");

    tree->addChild(compileExpression());

    while (true) {
        if(have("symbol", ",")){
            tree->addChild(new ParseTree("symbol", current()->getValue()));
            next();
        }else{
            break;
        }
        tree->addChild(compileExpression());
    }

    return tree;

}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    if (currentTokenIterator != tokens.end()) {
        currentTokenIterator++;
    }
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    if (currentTokenIterator != tokens.end()) {
        return *currentTokenIterator;
    } 
    else {
        throw std::out_of_range("Reached the end of the token list.");
    }
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    Token* currentToken = current();
    if(currentToken->getType() == expectedType && currentToken->getValue() == expectedValue){
        return true;
    }
    return false;
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    Token* currentToken = current();
    if(currentToken->getType() == expectedType && currentToken->getValue() == expectedValue){
        next();
        return currentToken;
    }else{
        throw ParseException();
    } 
}



/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "the program doesn't begin with a class";
}
