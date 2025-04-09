#ifndef READER_H
#define READER_H

#define INPUT_BUFFER_SIZE 256               // todo: put initializers in a config?

void read_input(char* buffer, int size);    // todo: should this be a size_t instead of an int?
void trim_newline(char* str);

#endif // READER_H