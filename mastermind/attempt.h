#ifndef ATTEMPT_H
#define ATTEMPT_H

#include "code.h"

// Opaque
typedef struct Attempt Attempt;

Attempt *attempt_create(const Code *guess, const Code *secret);
void attempt_destroy(Attempt *a);

const Code *attempt_get_guess(const Attempt *a);

int attempt_get_black(const Attempt *a);
int attempt_get_white(const Attempt *a);

void attempt_print(const Attempt *a, int index);

#endif
