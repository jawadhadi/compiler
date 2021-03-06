//
//  lex.h
//  Compiler
//
//  Created by Hadi on 01/11/2015.
//  Copyright © 2015 Hadi. All rights reserved.
//

#ifndef lex_h
#define lex_h


#include <iostream>
#include <string>
using namespace std;


const int KEY_COUNT = 14;
string buffer;
int currentIndex = 0;
bool endOfFile = false;

const char *keywords[KEY_COUNT] = { "integer", "function", "begin", "end", "return", "returns", "while", "if", "for", "void", "character", "print", "input", "else" };

bool isKeyword(string p) {
    
    bool flag = false;
    
    for (int i = 0; i < KEY_COUNT; i++) {
        if (p.compare(keywords[i]) == 0) {
            flag = true;
        }
    }
    
    return flag;
    
    
}


bool isLetter(char c) {
    
    bool flag = false;
    
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        flag = true;
    }
    
    return flag;
    
}

bool isDigit(char c) {
    
    bool flag = false;
    
    if (c >= '0' && c <= '9') {
        flag = true;
    }
    
    return flag;
    
}

bool isIdentifier(string &token, string &lexeme) {
    
    int state = 1;
    int startPosition = currentIndex; //to go back to intial index if this machine fails
    int c;
    int count = 0; //character count for identifier. MAX LIMIT = 15
    
    const int CHAR_LIMIT = 15;
    
    do{
        
        c = buffer[currentIndex];
        
        
        
        switch (state) {
            case 1:
                if (isLetter(c)) {
                    
                    if (count <= CHAR_LIMIT) {

                        count++;
                    }
                    
                    currentIndex++;
                    state = 2;
                    
                }
                else {
                    currentIndex = startPosition;
                    return false;
                }
                break;
            case 2:
                if (isLetter(c) || isDigit(c)) {
                    
                    if (count <= CHAR_LIMIT) {

                        count++;
                    }
                    currentIndex++;
                    
                }
                else {
                    
                    state = 3;
                    currentIndex++;
                }
                break;
            case 3:
                
                currentIndex--;
                if (currentIndex > startPosition) {
                    
                    string temp = buffer.substr(startPosition, count);
                    
                    if (isKeyword(temp)) {
                        
                        token = temp;
                        lexeme = "^";
                        return true;
                        
                    }
                    else {
                        
                        token = "ID";
                        lexeme = temp;
                        return true;
                        
                    }
                }
                break;
        }
        
    }while (1);
    
    return false;
}

bool isNumber(string &token, string &lexeme) {
    
    int state = 1;
    int startPosition = currentIndex;
    
    int c;
    
    do{
        
        c = buffer[currentIndex];
        
        switch (state) {
            case 1:
                if (c == '+' || c == '-') {
                    
                    
                    if (isDigit(buffer[(currentIndex) - 1])) {
                        
                        currentIndex = startPosition;
                        return false;
                    }
                    else {
                        
                        state = 2;
                        currentIndex++;
                        
                    }
                }
                else if (isDigit(c)) {
                    state = 3;
                    currentIndex++;
                }
                else {
                    currentIndex = startPosition;
                    return false;
                }
                break;
                
            case 2:
                if (isDigit(c)) {
                    state = 3;
                    currentIndex++;
                }
                else {
                    
                    currentIndex = startPosition;
                }
                break;
                
            case 3:
                if (isDigit(c)) {
                    state = 3;
                    currentIndex++;
                }
                else if (c == '.') {
                    
                    state = 4;
                    currentIndex++;
                }
                else if (c == 'E') {
                    
                    state = 6;
                    currentIndex++;
                }
                else {
                    
                    state = 9;
                    currentIndex++;
                }
                break;
                
            case 4:
                
                if (isDigit(c)) {
                    state = 5;
                    currentIndex++;
                }
                else {
                    
                    currentIndex = startPosition;
                }
                break;
                
            case 5:
                
                if (c == 'E') {
                    state = 6;
                    currentIndex++;
                }
                else if (isDigit(c)) {
                    
                    state = 5;
                    currentIndex++;
                }
                else {
                    
                    state = 9;
                    currentIndex++;
                }
                break;
                
            case 6:
                if (c == '+' || c == '-') {
                    state = 7;
                    currentIndex++;
                }
                else if (isDigit(c)) {
                    state = 8;
                    currentIndex++;
                    
                }
                else {
                    
                    currentIndex = startPosition;
                }
                break;
            case 7:
                if (isDigit(c)) {
                    state = 8;
                    currentIndex++;
                }
                else {
                    
                    currentIndex = startPosition;
    
                }
                break;
            case 8:
                if (isDigit(c)) {
                    state = 8;
                    currentIndex++;
                }
                else {
                    
                    state = 9;
                    currentIndex++;
                }
                break;
            case 9:
                
                currentIndex--;
                
                if (currentIndex > startPosition) {
                    
                    token = "NUM";
                    lexeme = buffer.substr(startPosition, currentIndex - startPosition);
                    return true;
                    
                }
                
                break;
                
        }
        
    }while (1);
    
    return false;
    
}

int isRO(string &token, string &lexeme) {
    
    int state = 1;
    int startPosition = currentIndex;
    int c;
    
     do{
        
        c = buffer[currentIndex];
        
        switch (state) {
            case 1:
                if (c == '=') {
                    state = 2;
                    currentIndex++;
                }
                else if (c == '<') {
                    state = 7;
                    currentIndex++;
                }
                else if (c == '>') {
                    state = 11;
                    currentIndex++;
                }
                else {
                    
                    currentIndex = startPosition;
                    return false;
                }
                break;
                
            case 2:
                
                if (c == '<') {
                    state = 3;
                    currentIndex++;
                }
                else if (c == '>') {
                    state = 4;
                    currentIndex++;
                }
                else if (c == '/') {
                    state = 5;
                    currentIndex++;
                }
                else {
                    
                    state = 6;
                    currentIndex++;
                }
                break;
                
            case 3:
                
                
                token = "RO";
                lexeme = "=<";
                return true;

            case 4:
                
                token = "RO";
                lexeme = "=>";
                return true;
                
            case 5:
                
                token = "RO";
                lexeme = "=/";
                return true;
            case 6:
                
                token = "RO";
                lexeme = "=";
                
                currentIndex--;
                
                return true;
                break;
            case 7:
                
                if (c == '-') {
                    state = 8;
                    currentIndex++;
                }else if (c == '='){
                    state = 9;
                    currentIndex++;
                }
                else {
                    
                    state = 10;
                    currentIndex++;
                }
                break;
            case 8:
                
                token = "<-";
                lexeme = "^";
                return true;
                
            case 9:
                
                token = "RO";
                lexeme = "<=";
                return true;
                
                
            case 10:
                
                token = "RO";
                lexeme = "<";
                currentIndex--;
                return true;
                
            case 11:
                
                token = "RO";
                lexeme = ">";
                return true;
                
        }
        
     }while(1);
    
    return false;
    
}

int isComment(string &token, string &lexeme) {
    
    int state = 1;
    int startPosition = currentIndex;
    int c;
    
    do{
        
        c = buffer[currentIndex];
        switch (state) {
            case 1:
                if (c == '*') {
                    state = 2;
                    currentIndex++;
                }
                else {
                    
                    currentIndex = startPosition;
                    return false;
                }
                break;
            case 2:
                if (c == '*') {
                    state = 3;
                    currentIndex++;
                }
                else {
                    
                    state = 8;
                    currentIndex++;
                }
                break;
            case 3:
                if (c == '*') {
                    state = 4;
                    currentIndex++;
                }
                else {
                    
                    currentIndex = startPosition;
                    return false;
                }
                break;
            case 4:
                if (c == '*') {
                    state = 5;
                    currentIndex++;
                }
                else {
                    state = 4;
                    currentIndex++;
                }
                break;
            case 5:
                
                if (c == '*') {
                    state = 6;
                    currentIndex++;
                }
                else {
                    state = 4;
                    currentIndex++;
                }
                break;
                
            case 6:
                
                if (c == '*') {
                    state = 7;
                    currentIndex++;
                }
                else if (isLetter(c) || isDigit(c) || c == ' ') {
                    state = 4;
                    currentIndex++;
                }
                else {
                    
                    currentIndex = startPosition;
                    return false;
                }
                break;
            case 7:
                
                token = "COMMENT";
                lexeme = "^";
                return true;
                
            case 8:
                
                token = "*";
                lexeme = "^";
                
                currentIndex--;
                
                return true;
  
        }
    }while(1);
    
    return false;
    
}

int isArithmetic(string &token, string &lexeme) {
    
    int startPosition = currentIndex;
    int c;
    c = buffer[currentIndex];
    
    if (c != '\0') {
        if (c == '/') {
            
            token = "/";
            lexeme = "^";
            currentIndex++;
            return true;
            
        }
        else if (c == '+') {
            
            token = "+";
            lexeme = "^";
            currentIndex++;
            return true;
        }
        else if (c == '-') {
            
            token = "-";
            lexeme = "^";
            currentIndex++;
            return true;
        }
        else {
            
            currentIndex = startPosition;
            return false;
        }

    }
    
    return false;
    
}



int isBracket(string &token, string &lexeme) {
    
    int startPosition = currentIndex;
    int c;
    
    c = buffer[currentIndex];
    
    if (c != '\0') {
        if (c == '[') {
            
            token = "[";
            lexeme = "^";
            currentIndex++;
            return true;
        }
        else if (c == ']') {
            
            token = "]";
            lexeme = "^";
            currentIndex++;
            return true;
        }
        else if (c == '(') {
            
            token = "(";
            lexeme = "^";
            currentIndex++;
            return true;    }
        else if (c == ')') {
            
            token = ")";
            lexeme = "^";
            currentIndex++;
            return true;
            
        }
        else if (c == ';') {
            
            token = ";";
            lexeme = "^";
            currentIndex++;
            return true;
        }
        else if (c == ',') {
            
            token = ",";
            lexeme = "^";
            currentIndex++;
            return true;
            
            
        }
        else {
            
            currentIndex = startPosition;
            return false;
        }
    }
    
    return false;
    
}

bool isLiteral(string &token, string &lexeme){
    
    int state = 1;
    int startPosition = currentIndex; //to go back to intial index if this machine fails
    int c;

    
    do{
        
        c = buffer[currentIndex];
        
        switch (state) {
            case 1:
                if (c == '\'') {
                    
                    currentIndex++;
                    state = 2;
                    
                }
                else {
                    currentIndex = startPosition;
                    return false;
                }
                break;
            case 2:
                if (isLetter(c) || isDigit(c)) {
                    
                    currentIndex++;
                    state = 3;
                    
                }
                else {
                    
                    currentIndex = startPosition;
                    return false;
                }
                break;
            case 3:
                
                if (c == '\'') {
                    
                    currentIndex++;
                    state = 4;
                    
                }
                else {
                    currentIndex = startPosition;
                    return false;
                }
                break;
                
             case 4:
                
                if (currentIndex > startPosition) {
                    
                    string temp = buffer.substr(startPosition, currentIndex - startPosition);
                    
                    if (isKeyword(temp)) {
                        
                        token = "literal";
                        lexeme = temp;
                        return true;
                        
                    }
                }
                
                break;
        }
        
    }while (1);
    
    return false;

    
}


void copyFileToString() {
    
    
    FILE * f = fopen("/Users/hadi/Developer/Compiler/Compiler/yal.txt", "r");
    
    
    if (f)
    {
        fseek(f, 0, SEEK_END);
        buffer.resize(ftell(f));
        rewind(f);
        fread(&buffer[0], 1, buffer.size(), f);
        fclose(f);
    }
    
    
}

bool getNextToken(string &token, string &lexeme) {
    
    if (buffer.empty()) {
        
        copyFileToString();
    }
    
    bool check = false;
    while (!check) {
        if(buffer[currentIndex] == ' ' || buffer[currentIndex] == '\n' || buffer[currentIndex] == '\t'){
            currentIndex++;
        }else{
            check = true;
        }
    }
    
    
    
    if (isIdentifier(token, lexeme)) {
        return true;
    }else if(isNumber(token, lexeme)){
        return true;
    }else if (isRO(token, lexeme)){
        return true;
    }else if (isComment(token, lexeme)){
        return true;
    }else if (isArithmetic(token, lexeme)){
        return true;
    }else if (isBracket(token, lexeme)){
        return true;
    }else if (isLiteral(token, lexeme)){
        return true;
    }
    
    if(buffer[currentIndex] == '\0'){
        
        endOfFile = true;
        
    }
    
    return false;
}

#endif /* lex_h */
