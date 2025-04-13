#define  _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "token.h"
#include "queue.h"
#include "stack.h"


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include "getline.h"
#endif


int isSymbol(char c){
  return (c =='+'|| c == '-' || c =='*' || c =='/' || c =='^' || c =='(' || c ==')' );
}


Queue * stringToTokenQueue(const char * expression){
	Queue * infix=createQueue();
	char * curpos=(char *)expression;

	Token * token;
	char  buff[11]; 
	int    len=0;
	char  * cur_dot=NULL;

	
	while(true){
	
		while (*curpos=='\n' || *curpos==' ')
			curpos++;

		if ( (*curpos>='0' && *curpos<='9') || *curpos=='.'){
			
			if (*curpos=='.'){
				if (cur_dot!=NULL){
					perror("\ninvalid number");
					exit(EXIT_FAILURE);
				}else{
					cur_dot=curpos;
				}
			}
			buff[len++]=*curpos;
		}else{
		
			if (len){
				if (buff[len-1]=='.'){
					perror("\ninvalid number");
					exit(EXIT_FAILURE);
				}
				
				buff[len]='\0';
				token=createTokenFromString(buff,len);
				
				len=0;
				cur_dot=NULL;
			}
			
			if (*curpos=='\0')
				break;
			
			if (isSymbol(*curpos)){
				token=createTokenFromString(curpos,1);
				infix=queuePush(infix, token);
			}else{
				
				perror("\ninvalid character");
				exit(EXIT_FAILURE);
			}
		}
		
		curpos++;
	}
	return infix;
}



Queue *shuntingYard(Queue* infix){
	Token * token;
	Token * token2;
	Queue * postfix=createQueue();
	Stack * stack=createStack(32);
	while( !queueEmpty(infix) ){
		token=(Token*)queueTop(infix);
		infix=queuePop(infix);
		if (tokenIsNumber(token)){
			postfix=queuePush(postfix,token);
		}else if (tokenIsOperator(token)){
			while 	(
						!stackEmpty(stack) &&
						(token2=(Token*)stackTop(stack)) &&
						tokenGetOperatorSymbol(token2)!='(' &&
						(
							tokenGetOperatorPriority(token2)>tokenGetOperatorPriority(token) ||
							( tokenGetOperatorPriority(token2)==tokenGetOperatorPriority(token) && tokenOperatorIsLeftAssociative(token) )
						)
					)
			{
					postfix=queuePush(postfix,token2);
					stack=stackPop(stack);
			}
			stack=stackPush(stack,token);
		}else if (tokenIsParenthesis(token) && tokenGetOperatorSymbol(token)=='('){
			stack=stackPush(stack,token);
		}else if (tokenIsParenthesis(token) && tokenGetOperatorSymbol(token)==')'){
			assert(!stackEmpty(stack));
			while ( (token2=(Token*)stackTop(stack)) && tokenGetOperatorSymbol(token2)!='(')
			{
				postfix=queuePush(postfix,token2);
				stack=stackPop(stack);
			}
			assert(tokenGetOperatorSymbol(token2)=='(');
			stack=stackPop(stack);
		}
	}
	while (!stackEmpty(stack) && (token2=(Token *)stackTop(stack)))
	{
		assert(!tokenIsParenthesis(token2));
		postfix=queuePush(postfix,token2);
		stack=stackPop(stack);
	}
	return postfix;
}

Token *evaluateOperator(Token *arg1, Token *op, Token *arg2){
	float b=tokenGetValue(arg1);
	float a=tokenGetValue(arg2);
	char o=tokenGetOperatorSymbol(op);
	float result=0;
	if (o=='+')
		result=a+b;
	else if (o=='-')
		result=a-b;
	else if (o=='*')
		result=a*b;
	else if (o=='/'){
		assert(b!=0);
		result=a/b;
	}else if (o=='^')
		result=pow(a,b);
	return createTokenFromValue(result);
}

float evaluateExpression(Queue* postfix) {
	Token * token;
	Token * operand_1;
	Token * operand_2;
	Stack * stack=createStack(0); 
	float result;
	while (!queueEmpty(postfix))
	{
		token=queueTop(postfix);
		postfix=queuePop(postfix);
		if (tokenIsOperator(token)){
			operand_1=stackTop(stack);
			stack=stackPop(stack);
			operand_2=stackTop(stack);
			stack=stackPop(stack);
			stack=stackPush(stack,evaluateOperator(operand_1,token,operand_2));
			
			deleteToken(&operand_1);
			deleteToken(&operand_2);
			deleteToken(&token);
		}else {
			stack=stackPush(stack,token);
		}
	}
	token=stackTop(stack);
	stack=stackPop(stack);
	result=tokenGetValue(token);

	
	deleteStack(&stack);
	deleteToken(&token);

	return result;
}




void printToken(FILE * f,void *e){
	Token * token=(Token*)e;
	tokenDump(f, token);
}


void computeExpressions(FILE *input){
    char * line = NULL;
    size_t len;
	ssize_t read;
	Queue * infix;
	Queue * postfix;
	float result;

    while ((read = getline(&line, &len, input)) != -1) {


		infix=stringToTokenQueue(line);
		if (queueSize(infix)>0){
			// print line
        	printf("input\t:\t%s",line);
			// print infix
			printf("infix\t:\t");
			queueDump(stdout, infix, &printToken);
			// print postfix
			postfix=shuntingYard(infix);
			printf("\npostfix\t:\t");
			queueDump(stdout, postfix, &printToken);
			// print result
			result=evaluateExpression(postfix);
			printf("\nevaluate\t:%f\t",result);
			printf("\n\n");
			deleteQueue(&postfix);
		}
		deleteQueue(&infix);


    }
    if (line)
        free(line);
}





/** Main function for testing.
 * The main function expects one parameter that is the file where expressions to translate are
 * to be read.
 *
 * This file must contain a valid expression on each line
 *
 */
int main(int argc, char **argv){
	FILE *input;

	if (argc<2) {
		fprintf(stderr,"usage : %s filename\n", argv[0]);
		return 1;
	}

	input = fopen(argv[1], "r");

	if ( !input ) {
		perror(argv[1]);
		return 1;
	}
	computeExpressions(input);

	// close file
	fclose(input);

	return 0;
}
