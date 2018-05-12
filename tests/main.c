/***************************************************************************//**

	@file         test_ftsh_functions.c

	@author       Max Bronckers

	@date         Thursday, 6 May 2018

	@brief        main.c tests

*******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include <criterion/options.h>
#include <criterion/output.h>
#include "ftsh_functions.h"
#include "ftsh.h"

int main(int argc, char *argv[]) {
    struct criterion_test_set *tests = criterion_initialize();

    criterion_options.jobs = 1;

    int result = 0;
    if (criterion_handle_args(argc, argv, true))
        result = !criterion_run_all_tests(tests);

    criterion_finalize(tests);
    return result;
}
