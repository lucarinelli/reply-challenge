//
// Created by federica on 15/03/18.
//

#include "math_functions.h"

float score(handle *h, order *o, project *p){
    float score=0,tp=0,f,avg,ov,tot;
    avg=avg_pr_latency(h,p,o);
    ov=ov_avail(h,p,o);
    tot=tot_pro_cost(h,p,o);

    tp=avg/ov*tot;
    f=fine(h,p,o);

    score=(1000000000)/(tp+f);
    return score;
}

float overall_quality_score(float avg_project_latency, float ov_avail_index,float tot_project_cost){
    float tp;
    if(ov_avail_index!=0)
        tp=(avg_project_latency/ov_avail_index)*tot_project_cost;
    else
        tp=0;
    return tp;
}

float avg_pr_latency(handle *h, project *p, order *o){
    float as=0,ur=0,lur=0;
    int i;

    order *tmp;
    for(tmp=o;tmp!=NULL;tmp=tmp->next)
        for(i=0;i<h->S_n_serv;i++)
            ur+=tmp->pack_n*h->providers[tmp->provider_id]->regions[tmp->region_id]->units_per_serv[i];

    for(tmp=o;tmp!=NULL;tmp=tmp->next)
        for(i=0;i<h->S_n_serv;i++)
            lur+=h->providers[tmp->provider_id]->regions[tmp->region_id]->latency_per_coun[p->country]*(tmp->pack_n*h->providers[tmp->provider_id]->regions[tmp->region_id]->units_per_serv[i]);
    if(ur==0)return 0;
    return lur/ur;
}

float ov_avail(handle *h, project *p, order *o){
    float overall,sum=0,availability=0,qi,qiq,tmpqi;
    int i;
    order *tmp;

    for(i=0;i<h->S_n_serv;i++){
        qi=0;
        qiq=0;
        for(tmp=o;tmp!=NULL;tmp=tmp->next){
            tmpqi=tmp->pack_n*h->providers[tmp->provider_id]->regions[tmp->region_id]->units_per_serv[i];
            qi+=tmpqi;
            qiq+=tmpqi*tmpqi;
        }
        qi=qi*qi;

        sum+=qi/qiq;
    }

    return sum/h->S_n_serv;
}

float tot_pro_cost(handle *h, project *p, order *o){
    order *tmp;
    float sum=0;
    for(tmp=o;tmp!=NULL;tmp=tmp->next){
        sum+=h->providers[tmp->provider_id]->regions[tmp->region_id]->package_unit_cost*tmp->pack_n;
    }
    return sum;
}

float fine(handle *h, project *p, order *o){
    float fine,fines;
    order *tmp;
    int sunits,i;

    for(i=0;i<h->S_n_serv;i++){
        fines = 0;
        for (tmp = o; tmp != NULL; tmp = tmp->next) {
            sunits += h->providers[tmp->provider_id]->regions[tmp->region_id]->units_per_serv[i] * tmp->pack_n;
        }
        fines = p->base_penalty * (p->units_per_service[i] - min(sunits,p->units_per_service[i])) / p->units_per_service[i];
    }

    return fine;
}

int min(int x,int y){
    return (x<y?x:y);
}