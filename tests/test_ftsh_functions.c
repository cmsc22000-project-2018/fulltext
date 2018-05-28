/***************************************************************************//**

	@file         test_ftsh_functions.c

	@author       Max Bronckers

	@date         Thursday, 2 May 2018

	@brief        ftsh_functions.c tests

*******************************************************************************/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <criterion/criterion.h>
#include "ftsh_functions.h"

Test(ftsh_functions, load) {
    char *path = "tests/test-file.txt";
    FILE *file = fopen(path, "r");

    char *args[2] = {"load", path};
    int rv = ftsh_load(args);

    cr_assert_eq(file, fp, "ftsh_load() did not load the file correctly");
}