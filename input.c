//
// Created by rinel on 3/15/2018.
//

#include "input.h"
#include "St.h"

handle *readInput(char *name){
    FILE *input;
    input=fopen(name,"r");
    if(input==NULL)printf("ERROR FILE");

    handle *h;
    h=(handle*)malloc(sizeof(handle));
    if(h==NULL)printf("ERROR ALLOCATING HANDLE");

    fscanf(input,"%d %d %d %d",&h->V_n_prov,&h->S_n_serv,&h->C_n_coun,&h->P_n_proj);

    int i,j,k;
    char tmp[100];//!!!!!!
    h->services=(char**)malloc(sizeof(char*)*h->S_n_serv);
    if(h->services==NULL)printf("ERROR 1");
    for(i=0; i<h->S_n_serv; i++){
        fscanf(input,"%s",tmp);
        h->services[i]=strdup(tmp);
    }

    h->countries=(char**)malloc(sizeof(char*)*h->C_n_coun);
    if(h->countries==NULL)printf("ERROR 2");

    h->st_countries=STinit(h->C_n_coun);

    for(i=0; i<h->C_n_coun; i++){
        fscanf(input,"%s",tmp);
        STinsert(h->st_countries, tmp);
        h->countries[i]=strdup(tmp);
    }

    h->providers=(provider**)malloc(sizeof(provider*)*h->V_n_prov);
    if(h->providers==NULL)printf("ERR ALL providers");

    for(i=0;i<h->V_n_prov;i++){
        h->providers[i]=(provider*)malloc(sizeof(provider));
        if(h->providers[i]==NULL)printf("ERR ALL provider i");
        fscanf(input,"%s %d",tmp,&h->providers[i]->n_regions);
        h->providers[i]->name=strdup(tmp);

        h->providers[i]->regions=(region**)malloc(sizeof(region*)*h->providers[i]->n_regions);
        if(h->providers[i]->regions==NULL)printf("ERR ALL REG");

        for(j=0;j<h->providers[i]->n_regions;j++){
            h->providers[i]->regions[j]=(region*)malloc(sizeof(region));
            if(h->providers[i]->regions==NULL)printf("ERR ALL REG j");

            fscanf(input,"%s %d %d",tmp,&h->providers[i]->regions[j]->available_packages,&h->providers[i]->regions[j]->package_unit_cost);

            h->providers[i]->regions[j]->units_per_serv=(int*)malloc(sizeof(int)*h->S_n_serv);
            if(h->providers[i]->regions[j]->units_per_serv==NULL)printf("ERR ALL UNITP");

            for(k=0;k<h->S_n_serv;k++){
                fscanf(input,"%d",&h->providers[i]->regions[j]->units_per_serv[k]);
            }

            h->providers[i]->regions[j]->latency_per_coun=(int*)malloc(sizeof(int)*h->C_n_coun);
            if(h->providers[i]->regions[j]->latency_per_coun==NULL)printf("ERR ALL LATC");

            for(k=0;k<h->C_n_coun;k++){
                fscanf(input,"%d",&h->providers[i]->regions[j]->latency_per_coun[k]);
            }
        }
    }

    h->projects=(project**)malloc(sizeof(project*)*h->P_n_proj);
    if(h->projects==NULL)printf("ERR ALL PROJ");

    for(i=0;i<h->P_n_proj;i++){
        h->projects[i]=(project*)malloc(sizeof(project));
        if(h->projects[i]==NULL)printf("ERR ALL PROJ i");

        fscanf(input,"%d %s",&h->projects[i]->base_penalty,tmp);

        h->projects[i]->country=STNomeIndice(h->st_countries, tmp);
        h->projects[i]->country_name=strdup(tmp);

        h->projects[i]->units_per_service=(int*)malloc(sizeof(int)*h->S_n_serv);
        if(h->projects[i]->units_per_service==NULL)printf("ERR ALL UNIPSE");

        for(j=0;j<h->S_n_serv;j++){
            fscanf(input,"%d",&h->projects[i]->units_per_service[j]);
        }
    }

    return h;
}