/// @file showpid.c
/// @brief
/// @copyright (c) 2014-2024 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    printf("pid %d\n", getppid());
    return 0;
}
