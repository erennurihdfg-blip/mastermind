#ifndef CODE_H
#define CODE_H

#include "peg.h"

// Opaque Code type
typedef struct Code Code;

Code *code_create(int length);
void code_destroy(Code *code);

int code_length(const Code *code);

int code_set_color(Code *code, int index, int color); // 1 ok, 0 fail
int code_get_color(const Code *code, int index);      // -1 on fail

Code *code_clone(const Code *other);

int code_fill_random(Code *code);

// Compare secret vs guess and compute feedback
void code_feedback(const Code *secret, const Code *guess, int *black, int *white);

void code_print(const Code *code); // prints like: R G B Y

#endif
