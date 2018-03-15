#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "solve.h"
#include "input.h"
#include "output.h"

#define FILENAME "input.txt"

int main(int argc, char **argv){
    handle *h;
    h=readInput(FILENAME);

    solve(h);

    output(h);
    printf("Andrea Bruno, bono!\n");
    return 0;
}