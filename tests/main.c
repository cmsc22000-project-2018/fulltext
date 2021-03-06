/***************************************************************************//**

	@file         test_ftsh_functions.c

	@file         test_parser.c

	@author       Max Bronckers

	@author       Cameron Dignan

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
//#include "parser.h"

int main(int argc, char *argv[]) {
    struct criterion_test_set *tests = criterion_initialize();

    criterion_options.jobs = 1;

    int result = 0;
    if (criterion_handle_args(argc, argv, true))
        result = !criterion_run_all_tests(tests);

    criterion_finalize(tests);
    //test_parser();
    return result;
}
