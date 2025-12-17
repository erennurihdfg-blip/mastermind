#ifndef GAME_H
#define GAME_H

#include "attempt.h"

// Opaque
typedef struct Game Game;

Game *game_create(int code_length, int max_attempts);
void game_destroy(Game *game);

int game_get_code_length(const Game *game);
int game_get_max_attempts(const Game *game);
int game_get_attempts_used(const Game *game);

int game_is_won(const Game *game);  // 1/0
int game_is_over(const Game *game); // 1/0

/* Submit guess string like "RGBY" (no spaces) or "R G B Y" (spaces allowed)
   Returns:
   1 = accepted
   0 = invalid input
  -1 = game already over
*/

int game_submit_guess_string(Game *game, const char *guess_str);

// Print history
void game_print_history(const Game *game);

// Print secret for end of game
void game_print_secret(const Game *game);

#endif
