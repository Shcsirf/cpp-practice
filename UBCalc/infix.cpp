// ============================================================================ 
// infix.cpp
// ~~~~~~~~~
// YOUR NAME
// - implement two functions, one to verify whether an infix expression is valid
//   and the other one evaluate the given infix expression
// ============================================================================ 
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stack>

#include "Lexer.h"
#include "Postfix_Evaluator.h"
#include "error_handling.h"
#include "infix.h"

using namespace std; // BAD practice

extern const string usage_msg = "UB Calculator Program. Version 0.1\n"
                                "  Author: YOUR NAME\n"
                                "  Report bugs to YOURID@buffalo.edu";

/**
 * -----------------------------------------------------------------------------
 * return true if the infix expression given by the token vector 'ie' is valid
 * false if it is invalid
 * we don't care whether the variables are defined in the expressions, thus
 * (a+0.4)*bcd - [(4+4.5)/2 - x]/3.0 is valid
 * even if the variables a, bcd, and x are not assigned previously
 * -----------------------------------------------------------------------------
 */
bool validate_infix_expr(vector<Token> ie)
{
    // YOUR CODE GOES HERE
	bool valid = true;
	stack<string> delimStack;
	int numberCounter = 0;
	int operatorCounter = 0;
	int divisionCounter = 0;
	for(int i=0; i< ie.size(); i++){
		if(ie.at(i).type == NUMBER){
			if((ie.at(i).value == "0")&&(divisionCounter == 1)){
					cerr << "Error: Cannot divide by zero" << endl;
					return false;
			}
			if(numberCounter == 1){
				cerr << "Error: Cannot have more than one number without an operator in between"
					<<endl;
				return false;
			}
			else{
				numberCounter++;
				if(operatorCounter > 0){
					operatorCounter--;
				}
				else if(divisionCounter > 0){
					divisionCounter;
				}
			}
		}
		if(ie.at(i).type == OPERATOR){
			if(operatorCounter == 1){
				cerr << "Error: Cannot have more than one operator without a number in between" << endl;
				return false;
			}
			else if(numberCounter == 0){
				cerr << "Error: must have a number before an operator" << endl;
				return false;
			}
			else{
				operatorCounter++;
				numberCounter--;
			}
		}
		if(ie.at(i).value == "/"){
			divisionCounter++;
		}
		else if(divisionCounter > 0){
			divisionCounter--;
		}
		if(ie.at(i).type == DELIM){
			if((ie.at(i).value == "[") || (ie.at(i).value == "{")||(ie.at(i).value == "(")){
				delimStack.push(ie.at(i).value);
			}
			else if((ie.at(i).value == "]") || (ie.at(i).value == "}")||(ie.at(i).value == ")")){
				if(delimStack.empty()){
					return false;
				}
				if((ie.at(i).value == "]")&&(delimStack.top() == "[")){
					delimStack.pop();
					valid = true;
				}
				else if((ie.at(i).value == "}")&&(delimStack.top() == "{")){
					delimStack.pop();
					valid = true;
				}
				else if((ie.at(i).value == ")")&&(delimStack.top() == "(")){
					delimStack.pop();
					valid = true;
				}
				else{
					valid = false;
					break;
				}
			}
		}
	}
	if(ie.empty()){
		valid = false;
		cerr << "Error: No expression was entered" << endl;
	}
	else if(operatorCounter > 0){
		valid = false;
		cerr << "Error: Can't have a operator without a number following it" << endl;
	}
	else if(delimStack.empty()){
		valid = true;
	}
	else{
		valid = false;
	}
    return valid;
}

/**
 * -----------------------------------------------------------------------------
 * convert an infix expression into postfix using the Shunting Yard algo
 * evaluate it and return, using the postfix evaluator
 * - ie is a token list of tokens forming the expression
 * - sym_tab is a symbol table, holding the values of variables already defined
 * - when anything goes not as expected, throw a runtime_error exception
 *   + undefined identifier (i.e. can't find it in sym_tab)
 *   + wrong infix expression (syntax error)
 *   + etc.
 * -----------------------------------------------------------------------------
 */
double eval_infix_expr(vector<Token> ie, map<string,double> sym_tab){
    vector<Token> postfix_expr;
    // convert ie in to a postfix expression, stored in postfix_expr
    
    // YOUR CODE GOES HERE

    // call the postfix evaluator to evaluate it
    Postfix_Evaluator pe(postfix_expr);
    return pe.eval();
}
