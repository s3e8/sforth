#ifndef FORTH_H
#define FORTH_H

#include <stdint.h>

/* Config */
#define MAX_WORD_LEN 32;
#define TIB_SIZE 256

typedef uintptr_t cell; // CELL ... is this a word?? 

/* Dictionary */
cell  *here;    // HERE - Next available/free memory
cell *latest;   // LATEST (or CONTEXT) - Pointer to most recent word
cell find();    // FIND [word]
void create(const char *name, void (*code)()) { // CREATE [word]
    
}
cell to_body(); // >BODY (to-body) - Converts execution token to parameter field address
cell body_of(); // same thing as above?? whats the correct... 
cell to_cfa();  // >CFA (to-c-f-a) - Converts word header to code field address
cell to_lfa();  // >LFA (to-l-f-a) - Gets link field address
cell to_nfa();  // >NFA (to-n-f-a) - Gets name field address

void tick();    // ' aka "tick"
void comma();   // "comma"

/* Memory Operations */
static inline void store(cell *addr, cell val) { *addr = val; }         // ! (store)    - Stores value at address (pronounced "store")
static inline cell fetch(const cell *addr) { return *addr; }            // @ (fetch)    - Fetches value from address (pronounced "fetch")
static inline void cstore(uint8_t *addr, uint8_t val) { *addr = val; }  // C! (c-store) - Stores byte
static inline uint8_t cfetch(const uint8_t *addr) { return *addr; }     // C@ (c-fetch) - Fetches byte
/* Dictionary pointer management */
static inline void allot(size_t cells) { here += cells; }               // ALLOT        - Reserves memory space

// Interpreter/Compiler
// STATE - Contains compiler flag (0=interpret, 1=compile)
// [ (left-bracket) - Enters interpret mode (immediate)
// ] (right-bracket) - Enters compile mode
// IMMEDIATE - Marks word as running during compilation
// COMPILE, - Compiles an execution token
// LITERAL - Compiles a number as literal
// POSTPONE - Compiles compilation behavior

/* Reader/Input */
void word(); // WORD - Reads space-delimited word from input
// BL (b-l) - Contains ASCII space (32)
void to_in(); // >IN (to-in) - Input buffer offset
// SOURCE - Current input buffer (addr, len)
// TIB (tib) - Terminal Input Buffer
// EVALUATE - Interprets a string
// REFILL - Attempts to fill input buffer
// QUIT - Main loop (top-level REPL)
// INTERPRET - Main interpreter

// Stack Operations

//     DUP (dupe) - Duplicates top stack item

//     DROP - Discards top stack item

//     SWAP - Swaps top two stack items

//     OVER - Copies second item to top

//     ROT (rote) - Rotates third item to top

//     >R (to-r) - Moves to return stack

//     R> (r-from) - Moves from return stack

//     R@ (r-fetch) - Copies from return stack



typedef struct word_t {
    cell flags;
    struct word_t *link;          // Forth calls this the "link (caps?) field" apparently (eg *next)
    char name[MAX_WORD_LEN];    // NAME field
} word_t;

cell  *dict_start;      // 
cell  *dict_end;        // 
word_t latest;          // LATEST [... word in dictionary]



#endif // FORTH_H