#include "code.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct Code
{
    int length;
    int *colors; // dynamic array of ints 0 to 5
};

static void seed_rng_once(void)
{
    static int seeded = 0;
    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }
}

Code *code_create(int length)
{
    if (length <= 0)
        return NULL;

    Code *c = (Code *)malloc(sizeof(Code));
    if (!c)
        return NULL;

    c->length = length;
    c->colors = (int *)malloc(sizeof(int) * (size_t)length);
    if (!c->colors)
    {
        free(c);
        return NULL;
    }

    for (int i = 0; i < length; i++)
        c->colors[i] = PEG_COLOR_MIN;
    return c;
}

void code_destroy(Code *code)
{
    if (!code)
        return;
    free(code->colors);
    free(code);
}

int code_length(const Code *code)
{
    return code ? code->length : 0;
}

static int valid_index(const Code *code, int index)
{
    return code && index >= 0 && index < code->length;
}

int code_set_color(Code *code, int index, int color)
{
    if (!valid_index(code, index))
        return 0;
    if (color < PEG_COLOR_MIN || color > PEG_COLOR_MAX)
        return 0;
    code->colors[index] = color;
    return 1;
}

int code_get_color(const Code *code, int index)
{
    if (!valid_index(code, index))
        return -1;
    return code->colors[index];
}

Code *code_clone(const Code *other)
{
    if (!other)
        return NULL;
    Code *c = code_create(other->length);
    if (!c)
        return NULL;
    for (int i = 0; i < other->length; i++)
        c->colors[i] = other->colors[i];
    return c;
}

int code_fill_random(Code *code)
{
    if (!code)
        return 0;
    seed_rng_once();
    for (int i = 0; i < code->length; i++)
    {
        int r = PEG_COLOR_MIN + (rand() % (PEG_COLOR_MAX - PEG_COLOR_MIN + 1));
        code->colors[i] = r;
    }
    return 1;
}

void code_feedback(const Code *secret, const Code *guess, int *black, int *white)
{
    if (!secret || !guess || secret->length != guess->length)
    {
        if (black)
            *black = 0;
        if (white)
            *white = 0;
        return;
    }

    int len = secret->length;
    int b = 0, w = 0;

    int *secret_used = (int *)calloc((size_t)len, sizeof(int));
    int *guess_used = (int *)calloc((size_t)len, sizeof(int));
    if (!secret_used || !guess_used)
    {
        free(secret_used);
        free(guess_used);
        if (black)
            *black = 0;
        if (white)
            *white = 0;
        return;
    }

    // black = correct color in correct position
    for (int i = 0; i < len; i++)
    {
        if (secret->colors[i] == guess->colors[i])
        {
            b++;
            secret_used[i] = 1;
            guess_used[i] = 1;
        }
    }

    // white = correct color wrong position
    for (int i = 0; i < len; i++)
    {
        if (guess_used[i])
            continue;
        for (int j = 0; j < len; j++)
        {
            if (secret_used[j])
                continue;
            if (guess->colors[i] == secret->colors[j])
            {
                w++;
                secret_used[j] = 1;
                guess_used[i] = 1;
                break;
            }
        }
    }

    free(secret_used);
    free(guess_used);

    if (black)
        *black = b;
    if (white)
        *white = w;
}

void code_print(const Code *code)
{
    if (!code)
        return;
    for (int i = 0; i < code->length; i++)
    {
        printf("%c", peg_color_to_char(code->colors[i]));
        if (i != code->length - 1)
            printf(" ");
    }
}
