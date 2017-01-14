/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TokenType.h
 * Author: ralitski
 *
 * Created on December 24, 2016, 2:06 AM
 */

#ifndef TOKENTYPE_H
#define TOKENTYPE_H

#include <iostream>
#include "Token.h"
#include "TokenTree.h"
#include "Expression.h"

class TokenType {
public:
    TokenType();
    TokenType(const TokenType& orig);
    virtual ~TokenType();
    
    virtual Token* parse(std::istream& stream) = 0; //return null, or a token
    virtual void parse(TokenTree* tree) = 0; //expand the tree wherever this token type is present, according to its own rules
    
    Expression* createExpression(TokenTree* tree);
    virtual Expression* createExpression(Expression* left, Expression* right) = 0;
private:
};

//constexpr TokenType PLUS;
//constexpr TokenType MINUS;
//constexpr TokenType MULTIPLY;
//constexpr TokenType DIVIDE;
//constexpr TokenType PARENTHESES_LEFT;
//constexpr TokenType PARENTHESES_RIGHT;
//constexpr TokenType VALUE;

//TODO---
//constexpr TokenType ASSIGN;
//constexpr TokenType VARIABLE;

#endif /* TOKENTYPE_H */

