#include "peg.h"
#include <stdlib.h>
#include <ctype.h>

typedef enum
{
    C_RED = PEG_RED,
    C_GREEN = PEG_GREEN,
    C_BLUE = PEG_BLUE,
    C_YELLOW = PEG_YELLOW,
    C_WHITE = PEG_WHITE,
    C_BLACK = PEG_BLACK
} PegColor;

struct Peg
{
    PegColor color;
};

static int is_valid_color(int c)
{
    return c >= PEG_COLOR_MIN && c <= PEG_COLOR_MAX;
}

Peg *peg_create(int color)
{
    if (!is_valid_color(color))
        return NULL;
    Peg *p = (Peg *)malloc(sizeof(Peg));
    if (!p)
        return NULL;
    p->color = (PegColor)color;
    return p;
}

void peg_destroy(Peg *peg)
{
    free(peg);
}

int peg_get_color(const Peg *peg)
{
    return peg ? (int)peg->color : -1;
}

int peg_set_color(Peg *peg, int color)
{
    if (!peg || !is_valid_color(color))
        return 0;
    peg->color = (PegColor)color;
    return 1;
}

char peg_color_to_char(int color)
{
    switch (color)
    {
    case PEG_RED:
        return 'R';
    case PEG_GREEN:
        return 'G';
    case PEG_BLUE:
        return 'B';
    case PEG_YELLOW:
        return 'Y';
    case PEG_WHITE:
        return 'W';
    case PEG_BLACK:
        return 'K'; // K = black
    default:
        return '?';
    }
}

int peg_char_to_color(char c)
{
    c = (char)toupper((unsigned char)c);
    switch (c)
    {
    case 'R':
        return PEG_RED;
    case 'G':
        return PEG_GREEN;
    case 'B':
        return PEG_BLUE;
    case 'Y':
        return PEG_YELLOW;
    case 'W':
        return PEG_WHITE;
    case 'K':
        return PEG_BLACK;
    default:
        return -1;
    }
}

const char *peg_color_name(int color)
{
    switch (color)
    {
    case PEG_RED:
        return "Red";
    case PEG_GREEN:
        return "Green";
    case PEG_BLUE:
        return "Blue";
    case PEG_YELLOW:
        return "Yellow";
    case PEG_WHITE:
        return "White";
    case PEG_BLACK:
        return "Black";
    default:
        return "Invalid";
    }
}
