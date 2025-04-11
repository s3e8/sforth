#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "stack.h"
#include <stdint.h>
#include <stdbool.h>

#define BIT(x) (1<<(x))         // ...
#define FLAG_HIDDEN     BIT(0)  // 0b00000001
#define FLAG_IMMED      BIT(1)  // 0b00000010
#define FLAG_BUILTIN    BIT(2)  // 0b00000100
#define FLAG_HASHARG    BIT(3)  // 0b00001000
#define FLAG_INLINE     BIT(4)  // 0b00010000
#define FLAG_DEFFERED   BIT(5)  // 0b00100000

#define STATE_IMMEDIATE 0
#define STATE_COMPILE   1

#define MAX_WORD_LEN 32



#endif // INTERPRETER_H