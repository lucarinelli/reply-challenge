#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "solve.h"
#include "input.h"
#include "output.h"

int main(int argc, char **argv){
    handle *h;
    h=readInput("first_adventure.in");

    solve(h);

    output(h);
    printf("Andrea Bruno, bono!\n");
    return 0;
}