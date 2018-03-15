//
// Created by rinel on 3/15/2018.
//

#include "output.h"

#define FILENAME_OUTPUT "output.txt"

void output(handle *h){
    FILE *output;
    fopen(FILENAME_OUTPUT,"w");
    int i;

    for(i=0;i<h->P_n_proj;i++){

        fprintf(output,"%d",)
    }
}