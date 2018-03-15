//
// Created by rinel on 3/15/2018.
//

#include "solve.h"

int fit(project *p_sat, project *p_act, region *r, int S){
    int i,needed,n=0,p=0;
    for(i=0;i<S;i++){
        if(p_act->units_per_service[i]<p_sat->units_per_service[i]){
            needed=p_sat->units_per_service[i]-p_act->units_per_service[i];
            p=needed/r->units_per_serv[i];
            if(p>n)p=n;
        }
    }
    return n;
}

void solve_p_r(handle *h, int i, project *p_act, order **o, int posP, int posR){
    if(posP==h->V_n_prov)return;
    if(posR==h->providers[posP]->n_regions)return solve_p_r(h,i,p_act,o,posP+1,0);

    order *tmp=(order*)malloc(sizeof(order));
    tmp->pack_n=fit(h->projects[i],p_act,h->providers[posP]->regions[posR],h->S_n_serv);
    tmp->provider_id=posP;
    tmp->region_id=posR;
    tmp->next=*o;
    *o=tmp;
    solve_p_r(h,i,p_act,o,posP,posR+1);
    tmp=(*o)->next;
    free(*o);
    *o=tmp;
    solve_p_r(h,i,p_act,o,posP,posR+1);

}

void solve_p(handle *h, int i){
    int j;
    order *o;
    project *p;
    p=(project*)malloc(sizeof(project));
    for(j=0;j<h->S_n_serv;j++)
        p->units_per_service[j]=0;
    solve_p_r(h,i,p,&o,0,0);
}

void solve(handle *h){
    int i;

    for(i=0;i<h->P_n_proj;i++){
        solve_p(h,i);
    }
}