/***************************************************************************//**

	@file         test_ftsh.c

	@author       Max Bronckers

	@date         Thursday, 2 May 2018

	@brief        ftsh.c tests

*******************************************************************************/

#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ftsh.h"

Test(ftsh, input)
{
    char sample[] = "This is a sample";
    char *expected[] = {"This", "is", "a", "sample"};
    char **actual = ftsh_get_input(sample);

    for (int i=0; actual[i] != NULL; i++) {
        cr_assert_str_eq(actual[i], expected[i], "error inputs");
    }
}
