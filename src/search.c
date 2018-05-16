#include "search.h"
#include "ftsh.h"
#include "ftsh_functions.h"

void search(char** word_set, int SET_SIZE, stringArray* pf) {
    for (int i = 0; i < pf->len; i++) {
        for (int j = 0; j < SET_SIZE; j++) {
            if (strcmp(word_set[j], pf->array[i]) == 0) {
                // add to list of matches
            }
        }
    }

    // call output() that prints found results and allows user to interact
}


