#include "game.h"
#include "peg.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

struct Game
{
    Code *secret;
    Attempt **attempts; // dynamic array of pointers
    int attempt_count;
    int max_attempts;
    int code_length;
    int won;
};

static int parse_guess_to_code(const char *s, int len, Code *out)
{
    // Accept "RGBY" OR "R G B Y"
    int idx = 0;

    for (const char *p = s; *p && idx < len; p++)
    {
        if (isspace((unsigned char)*p))
            continue;

        int c = peg_char_to_color(*p);
        if (c < 0)
            return 0;

        if (!code_set_color(out, idx, c))
            return 0;
        idx++;
    }

    // must have exactly length pegs and no extra non-space chars after
    if (idx != len)
        return 0;

    for (const char *p = s; *p; p++)
    {
        if (isspace((unsigned char)*p))
            continue;
        // Count non-space chars to ensure it equals length
    }

    // also reject if there are more non-space chars than length
    int nonspace = 0;
    for (const char *p = s; *p; p++)
        if (!isspace((unsigned char)*p))
            nonspace++;
    if (nonspace != len)
        return 0;

    return 1;
}

Game *game_create(int code_length, int max_attempts)
{
    if (code_length <= 0 || max_attempts <= 0)
        return NULL;

    Game *g = (Game *)malloc(sizeof(Game));
    if (!g)
        return NULL;

    g->code_length = code_length;
    g->max_attempts = max_attempts;
    g->attempt_count = 0;
    g->won = 0;

    g->secret = code_create(code_length);
    if (!g->secret)
    {
        free(g);
        return NULL;
    }
    code_fill_random(g->secret);

    g->attempts = (Attempt **)malloc(sizeof(Attempt *) * (size_t)max_attempts);
    if (!g->attempts)
    {
        code_destroy(g->secret);
        free(g);
        return NULL;
    }
    for (int i = 0; i < max_attempts; i++)
        g->attempts[i] = NULL;

    return g;
}

void game_destroy(Game *game)
{
    if (!game)
        return;
    for (int i = 0; i < game->attempt_count; i++)
        attempt_destroy(game->attempts[i]);
    free(game->attempts);
    code_destroy(game->secret);
    free(game);
}

int game_get_code_length(const Game *game) { return game ? game->code_length : 0; }
int game_get_max_attempts(const Game *game) { return game ? game->max_attempts : 0; }
int game_get_attempts_used(const Game *game) { return game ? game->attempt_count : 0; }

int game_is_won(const Game *game) { return game ? game->won : 0; }

int game_is_over(const Game *game)
{
    if (!game)
        return 1;
    return game->won || game->attempt_count >= game->max_attempts;
}

int game_submit_guess_string(Game *game, const char *guess_str)
{
    if (!game || !guess_str)
        return 0;
    if (game_is_over(game))
        return -1;

    Code *guess = code_create(game->code_length);
    if (!guess)
        return 0;

    if (!parse_guess_to_code(guess_str, game->code_length, guess))
    {
        code_destroy(guess);
        return 0;
    }

    Attempt *a = attempt_create(guess, game->secret);
    code_destroy(guess);
    if (!a)
        return 0;

    game->attempts[game->attempt_count++] = a;

    if (attempt_get_black(a) == game->code_length)
        game->won = 1;
    return 1;
}

void game_print_history(const Game *game)
{
    if (!game)
        return;

    printf("\n--- Attempts (%d/%d) ---\n", game->attempt_count, game->max_attempts);
    for (int i = 0; i < game->attempt_count; i++)
    {
        attempt_print(game->attempts[i], i + 1);
    }
    printf("\n");
}

void game_print_secret(const Game *game)
{
    if (!game)
        return;
    printf("Secret: ");
    code_print(game->secret);
    printf("\n");
}
