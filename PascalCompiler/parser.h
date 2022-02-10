#ifndef PARSER_H_
#define PARSER_H_

#include "stack.h"
#include "tokens.h"

int parser(Stack stack, int inputToken, int currentToken);

int verifyToken(int token, int currentToken);

#endif