#include <stdio.h>
#include <stdlib.h>
#include "e.h"

int main(int argc, char* argv[]) {

    if (argc<3) {
        fprintf(stderr,"Syntax: %s infile outfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return copy(argv[1], argv[2]);
}
