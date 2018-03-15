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
        order *tmp;
        tmp=h->projects[i]->orders;
        if(tmp==NULL){printf("\n");continue;}
        for(;tmp!=NULL;tmp=tmp->next){
            fprintf(output,"%d %d %d",tmp->provider_id,tmp->region_id,tmp->pack_n);
        }
    }
}