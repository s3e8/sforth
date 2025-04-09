#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdint.h>

typedef uintptr_t cell;

#define  STACK_SIZE 64
#define RSTACK_SIZE 64
extern cell   ds[STACK_SIZE];               // -- data stack (grows downward)
extern cell  *ds_top;                       // todo: should I call this bottom? 
extern void  *rs[RSTACK_SIZE];              // -- return stack 
extern void **rs_top;                       // todo: is this more canonically of type "cell" rather than type void*?

#define PUSH(x)     (*--ds_top = (cell)(x)) // -- helper macros
#define POP()       (*ds_top++)
#define RPUSH(x)    (*rs_top = (void*)(x))
#define RPOP()      (*rs_top++)
#define TOP         (ds_top[0])             // -- todo: how does this reset the top?

void stack_init();
void stack_destroy();
void print_stack();

#endif // STACK_H