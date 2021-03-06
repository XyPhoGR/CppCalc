/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ralitski
 *
 * Created on December 24, 2016, 1:52 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <functional>
#include <time.h>
using namespace std;

#include "Calculator.h"
#include "Expression.h"
#include "Token.h"
#include "TokenTree.h"
#include "TokenType.h"
#include "TokenTypeBinaryOperator.h"
#include "TokenTypeLeftParentheses.h"
#include "TokenTypeMultiBinaryOperator.h"
#include "TokenTypeNumber.h"
#include "TokenTypeUnaryOperator.h"
#include "TokenTypeUnknown.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    //TODO: a calculator that reads tokens out of cin, stores them in a syntax tree, and evaluates.
    //runs multi-line like an interpreter and can use variables.
    
    Calculator c;
    std::vector<TokenType*>& types = c.getTokenTypes();
    
    //order matters
    
    types.push_back(new TokenTypeNumber{});
    types.push_back(new TokenTypeLeftParentheses{});
    types.push_back(new TokenTypeUnknown{')'});
    //two negative symbols - easier than allowing - to be binary and unary
    types.push_back(new TokenTypeUnaryOperator{'_', [](double d) {return -d;}});
    types.push_back(new TokenTypeUnaryOperator{'~', [](double d) {return -d;}});
    
    TokenTypeMultiBinaryOperator* oper1 = new TokenTypeMultiBinaryOperator{};
    oper1->addOperator('*', [](double a, double b) {return a * b;});
    oper1->addOperator('/', [](double a, double b) {return a / b;});
    types.push_back(oper1);
    
    TokenTypeMultiBinaryOperator* oper2 = new TokenTypeMultiBinaryOperator{};
    oper2->addOperator('+', [](double a, double b) {return a + b;});
    oper2->addOperator('-', [](double a, double b) {return a - b;});
    types.push_back(oper2);

//TODO---
    //positive and negative (unary)
//TokenTypeBinaryOperator ASSIGN{"="};
//TokenType VARIABLE;
    
    while(true) {
        try {
            cout << " Input: ";
            TokenTree* tree = c.read(cin);
            cout << " Output: ";
            if(tree == nullptr) cout << "nullptr";
            else cout << *tree;
            cout << endl;
            tree = c.parse(tree);
            cout << " Parsed: ";
            if(tree == nullptr) cout << "nullptr";
            else cout << *tree;
            cout << endl;

            Expression* e = tree->express();
            cout << " Value: ";
            if(e == nullptr) cout << "nullptr";
            else cout << e->getValue();
            cout << endl;

            cout << endl;
        } catch(...) {
            cout << endl << "Error." << endl;
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    return 0;
}

