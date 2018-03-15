//
// Created by Andrea on 15/03/2018.
//

#ifndef REPLY_CHALLENGE_ST_H
#define REPLY_CHALLENGE_ST_H

typedef struct symboltable *ST;

ST STinit(int N);
int STinsert(ST st, char *nome);
int STNomeIndice(ST st, char *nome);
char* STIndiceNome(ST st, int indice);
void STfree(ST st);


#endif //REPLY_CHALLENGE_ST_H
