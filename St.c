//
// Created by Andrea on 15/03/2018.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "St.h"

/*Open addressing e linear probing. Aggiungo due vettori di indici per
operare la conversione da indice a nome e fornire indici ordinati
(la tabella è infatti inizializzata al doppio della dimensione massima
 per ridurre le collisioni)*/

struct symboltable{
    char **tabella;
    int *hash_indice, *indice_hash;
    int num, max;
};

int hash(char *nome, int N);

ST STinit(int N){
    int i;

    ST st=malloc(sizeof(*st));
    st->num=0;
    st->max=2*N;

    st->tabella=malloc((st->max)*sizeof(*(st->tabella)));
    for(i=0; i<st->max; i++){st->tabella[i]=NULL;}

    st->hash_indice=malloc((st->max)*sizeof(int));
    for(i=0; i<st->max; i++){st->hash_indice[i]=-1;}

    st->indice_hash=malloc((st->max)*sizeof(int));
    for(i=0; i<st->max; i++){st->indice_hash[i]=-1;}
    return st;
}

int hash(char *nome, int N){
    int h, base=127;
    for(h=0; *nome!='\0'; nome++){
        h=(base*h+(*nome))%(2*N);
    }
    return h;
}

int STinsert(ST st, char *nome){
    ST st_new;
    int i, p;

    if(st->num>=(st->max)/2){
        st_new=STinit(2*(st->max));
        for(i=0; i<st->num; i++){
            p=st->indice_hash[i];              //Reinserisco gli elementi nell'ordine degli indici
            STinsert(st_new, st->tabella[p]);  //per non alterarli.
        }
        STfree(st);
        *st=*st_new;
    }

    int h=hash(nome, st->max);

    while(st->tabella[h]!=NULL){h=(h+1)%(st->max);}
    st->tabella[h]=strdup(nome);

    st->hash_indice[h]=st->num;
    st->indice_hash[st->num]=h;

    st->num++;
    return (st->num)-1;
}

int STNomeIndice(ST st, char *nome){
    int h=hash(nome, st->max);

    while(st->tabella[h]!=NULL){
        if(strcmp(st->tabella[h], nome)!=0){h=(h+1)%(st->max);}
        else{return st->hash_indice[h];}
    }
    return -1;
}

char* STIndiceNome(ST st, int indice){
    int h=st->indice_hash[indice];

    if(h==-1){return NULL;}
    return st->tabella[h];
}

void STfree(ST st){
    int i;

    free(st->hash_indice);
    free(st->indice_hash);

    for(i=0; i<st->max; i++){free(st->tabella[i]);}
    free(st->tabella);
    free(st);
}
