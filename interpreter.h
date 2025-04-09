#ifndef INTERPRETER_H
#define INTERPRETER_H

extern void **ip;
#define NEXT goto **ip;

void execute_word();
void interpret();
void forth_run();

#endif // INTERPRETER_H