/// @file nice.c
/// @brief
/// @copyright (c) 2014-2024 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc == 1) {
        int current = nice(0);
        printf("%d\n", current);
        return 0;
    }
    if (argc != 2) {
        printf("%s: missing operand.\n", argv[0]);
        printf("Try '%s --help' for more information.\n", argv[0]);
        return 1;
    }
    if (!strcmp(argv[1], "--help")) {
        printf("Usage: %s <increment>\n", argv[0]);
        return 0;
    }
    char *endptr;
    long increment = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || increment < -40 || increment > 40) {
        printf("Error: You must provide a value between (-40,+40).\n");
        return 1;
    }
    int newNice = nice(increment);
    printf("Your new nice value is %d.\n", newNice);
    return 0;
}
