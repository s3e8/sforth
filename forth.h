#ifndef FORTH_H
#define FORTH_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* Config */
#define MAX_WORD_LEN 32;
#define TIB_SIZE 256

typedef uintptr_t cell; // CELL ... is this a word?? 

/* Dictionary */
cell  *here;    // HERE - Next available/free memory
cell *latest;   // LATEST (or CONTEXT) - Pointer to most recent word
cell find();    // FIND [word]
void create(const char *name) { // CREATE [word]
    // 1. Store link to previous word
    store(here, (cell)latest);
    cell *header = here++;

    // 2. Store length/flags (bit 7=immediate flag)
    uint8_t len = strlen(name);
    cstore((uint8_t *)here, len);
    here++;

    // 3. Store name string
    memcpy(here, name, len + 1);  // Include null terminator
    here = (cell *)((char *)here + len + 1);

    // 4. Align to cell boundary
    here = (cell *)(((uintptr_t)here + sizeof(cell)-1) & ~(sizeof(cell)-1));

    // Update LATEST
    latest = header;
}
cell to_body(); // >BODY (to-body) - Converts execution token to parameter field address
cell body_of(); // same thing as above?? whats the correct... 
cell to_cfa();  // >CFA (to-c-f-a) - Converts word header to code field address
cell to_lfa();  // >LFA (to-l-f-a) - Gets link field address
cell to_nfa();  // >NFA (to-n-f-a) - Gets name field address

cell *tick() {    // ' aka "tick"
    char *name = word(' ');
    cell *xt = find(name);
    if (!xt) error("Undefined word");
    return xt;
}
void comma(cell val) {   // "comma"
    store(here++, val);
}

/* Memory Operations */
static inline void store(cell *addr, cell val) { *addr = val; }         // ! (store)    - Stores value at address
static inline cell fetch(const cell *addr) { return *addr; }            // @ (fetch)    - Fetches value from address
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

// where does this func go? 
void execute(cell *xt) {
    ((void (*)())*xt)();  // Call through the function pointer
}

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

void test_dictionary() {
    // Initialize
    cell memory[1024];
    here = memory;
    latest = NULL;
    
    // Create test words
    create("TEST");
    comma((cell)primitive_test);  // Store XT
    
    create("ANSWER");
    comma(42);  // Store literal value
    
    // Test FIND
    cell *test_xt = find("TEST");
    assert(test_xt != NULL);
    
    cell *answer_xt = find("ANSWER");
    assert(answer_xt != NULL);
    assert(fetch(answer_xt) == 42);
    
    // Test TICK
    printf("Enter word name: ");
    char input[32];
    fgets(input, sizeof(input), stdin);
    cell *found = tick(input);
    printf("Found at %p\n", found);
    
    printf("Dictionary tests passed!\n");
}



#endif // FORTH_H