#ifndef PEG_H
#define PEG_H

// Opaque
typedef struct Peg Peg;

#define PEG_RED 0
#define PEG_GREEN 1
#define PEG_BLUE 2
#define PEG_YELLOW 3
#define PEG_WHITE 4
#define PEG_BLACK 5

#define PEG_COLOR_MIN PEG_RED
#define PEG_COLOR_MAX PEG_BLACK

Peg *peg_create(int color);
void peg_destroy(Peg *peg);

int peg_get_color(const Peg *peg);
int peg_set_color(Peg *peg, int color); // returns 1 ok, 0 invalid

char peg_color_to_char(int color); // 0..5 - 'R','G','B','Y','W','K'
int peg_char_to_color(char c);     // 'R'.. -> 0..5 or -1 invalid
const char *peg_color_name(int color);

#endif
