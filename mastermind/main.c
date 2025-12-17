#include <stdio.h>
#include <string.h>

#include "game.h"

static void trim_newline(char *s)
{
    if (!s)
        return;
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n')
        s[n - 1] = '\0';
}

static void print_rules(int code_len)
{
    printf("=== Mastermind ===\n");
    printf("Goal: guess the secret code in a limited number of attempts.\n");
    printf("Feedback:\n");
    printf("  Black = correct color in the correct position\n");
    printf("  White = correct color but in the wrong position\n\n");

    printf("Colors (classic):\n");
    printf("  R = Red\n");
    printf("  G = Green\n");
    printf("  B = Blue\n");
    printf("  Y = Yellow\n");
    printf("  W = White\n");
    printf("  K = Black\n\n");

    printf("Enter your guess as %d letters.\n", code_len);
    printf("Examples: RGBY  or  R G B Y\n\n");
}

int main(void)
{
    const int CODE_LEN = 4;
    const int MAX_ATTEMPTS = 10;

    Game *game = game_create(CODE_LEN, MAX_ATTEMPTS);
    if (!game)
    {
        printf("Failed to start game.\n");
        return 1;
    }

    print_rules(CODE_LEN);

    char input[256];

    while (!game_is_over(game))
    {
        printf("Enter guess (%d letters): ", game_get_code_length(game));
        if (!fgets(input, sizeof(input), stdin))
            break;
        trim_newline(input);

        int result = game_submit_guess_string(game, input);
        if (result == -1)
            break;
        if (result == 0)
        {
            printf("Invalid guess. Use %d letters from R,G,B,Y,W,K.\n\n", game_get_code_length(game));
            continue;
        }

        game_print_history(game);

        if (game_is_won(game))
        {
            printf(" You cracked the code!\n");
            break;
        }
    }

    if (!game_is_won(game) && game_is_over(game))
    {
        printf("Game over: you ran out of attempts.\n");
    }

    game_print_secret(game);
    game_destroy(game);
    return 0;
}
