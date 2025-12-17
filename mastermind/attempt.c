#include "attempt.h"
#include <stdlib.h>
#include <stdio.h>

struct Attempt
{
    Code *guess;
    int black;
    int white;
};

Attempt *attempt_create(const Code *guess, const Code *secret)
{
    if (!guess || !secret)
        return NULL;

    Attempt *a = (Attempt *)malloc(sizeof(Attempt));
    if (!a)
        return NULL;

    a->guess = code_clone(guess);
    if (!a->guess)
    {
        free(a);
        return NULL;
    }

    code_feedback(secret, guess, &a->black, &a->white);
    return a;
}

void attempt_destroy(Attempt *a)
{
    if (!a)
        return;
    code_destroy(a->guess);
    free(a);
}

const Code *attempt_get_guess(const Attempt *a)
{
    return a ? a->guess : NULL;
}

int attempt_get_black(const Attempt *a)
{
    return a ? a->black : 0;
}

int attempt_get_white(const Attempt *a)
{
    return a ? a->white : 0;
}

void attempt_print(const Attempt *a, int index)
{
    if (!a)
        return;
    printf("%d) ", index);
    code_print(a->guess);
    printf(" | Black: %d  White: %d\n", a->black, a->white);
}
