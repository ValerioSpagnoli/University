#include "../e2A.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void multi_get_env(const char** names, char*** values, int num) {
    int i;
    *values = malloc(num*sizeof(char**));
    assert(*values != NULL);
    for (i=0; i<num; ++i) {
        char* env = getenv(names[i]);
        if (env == NULL) (*values)[i] = NULL;
        else {
            (*values)[i] = malloc(strlen(env)*sizeof(char)+1);
            assert((*values)[i] != NULL);
            strcpy((*values)[i], env);
        }
    }
}
