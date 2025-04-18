
#ifndef __STACK_H__
#define __STACK_H__
#include <stdio.h>
#include <stdbool.h>

/** Opaque definition of type Stack */
typedef struct s_stack Stack;
typedef Stack *ptrStack;

/** Create and initialize an empty stack.
 * @param max_size : max number of element that the stack will contains.
 * This operator creates an empty stack of the required capacity.
 * @note If max_size is 0, the capacity of the stack will be fixed by the implementation and is a least 32.
 */
Stack *createStack(int max_size);

/** Delete the stack.
 */
void deleteStack(ptrStack *s);

/** Push a value on the stack.
 * @param s : the Stack to push on.
 * @param e : the value to push on the stack.
 * @return the modified stack.
 * @note implemented using side effect on the stack. After execution, s is the same than the returned stack.
 */
Stack *stackPush(Stack *s, void * e);

/** Test if a stack is empty.
 * @param s : the Stack to test.
 * @return : true if the stack is empty, else false.
 */
bool stackEmpty(Stack *s);

/** Pop a value from the stack.
 * @pre pop(s) defined if \f$\neg\f$ empty(s)
 * @param s : the Stack to pop from.
 * @return the modified stack.
 * @note implemented using side effect on the stack. After execution, s is the same than the returned stack.
 */
Stack *stackPop(Stack *s);

/** Return the top of a stack.
 * @pre top(s) defined if \f$\neg\f$ empty(s)
 * @param s : the Stack to examine.
 * @return the value at the top of the stack.
 */
void *stackTop(Stack *s);

/** Return true if the stack will overflow on the next push.
 * @param s : the Stack to examine.
 * @return true if the number of element in the stack is equal to the stack capacity, else false.
 */
bool stackOverflow(Stack *s);

/** Dump the stack (print it) on the given FILE*
 * Dump the stack using the provided function that must dump the data to the given FILE*.
 */
void stackDump(FILE *f, Stack *s, void(*dumpfunction)(FILE *f, void *e));

#endif
