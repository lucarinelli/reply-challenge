//
// Created by federica on 15/03/18.
//

#include "math_functions.h"

float overall_quality_score(float avg_project_latency, float ov_avail_index,float tot_project_cost){
    float tp;
    if(ov_avail_index!=0)
        tp=(avg_project_latency/ov_avail_index)*tot_project_cost;
    else
        tp=0;
    return tp;
}

float avg_pr_latency(float *lat_per_region, int *n_service_units, int n_regions){
    float as=0,ur=0,tmp=0;
    for (int i = 0; i <n_regions ; ++i) {
        ur+=n_service_units[i];
    }
    if(ur!=0){
        for (int i = 0; i <n_regions ; ++i) {
            tmp+=(n_service_units[i])*(lat_per_region[i]);
        }
        as=tmp/ur;
    } else
        as=0;
    return as;
}

float ov_avail_index(int *units_bought_reg,int n_regions){
    float ov_ail,num,num_tmp=0,den=0;
    for (int i = 0; i <n_regions ; ++i) {
        num_tmp+=units_bought_reg[i];
        den+=(units_bought_reg[i])*units_bought_reg[i];
    }
    if(den!=0){
        num=num_tmp*num_tmp;
        ov_ail=num/den;
    }
    else
        ov_ail=0;
    return ov_ail;
}

float tot_pro_cost(float package_fee,int min_pack, int pack_bought){ //?
    float tot=pack_bought*package_fee*min_pack;
    return tot;
}

float fine(int penalty_base,int units_needed, int sum_alloc_units){
    float fine;
    if(units_needed!=0){
        fine=penalty_base*((units_needed-min(units_needed,sum_alloc_units))/units_needed);
    }
    else
        fine=0;
    return fine;
}

int min(int x,int y){
    return (x<y?x:y);
}