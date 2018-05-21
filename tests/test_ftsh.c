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
    char *sample = "This is a sample";
    char *expected[] = {"This", "is", "a", "sample"};

    cr_assert_eq(expected, ftsh_get_input(sample), "input error");
}
