//
// Created by federica on 15/03/18.
//

#ifndef REPLY_CHALLENGE_MATH_FUNCTIONS_H
#define REPLY_CHALLENGE_MATH_FUNCTIONS_H

#include "datastructure.h"

float overall_quality_score(float avg_project_latency, float ov_avail_index, float tot_project_cost);
float avg_pr_latency(int *lat_per_region, int *n_service_units, int n_regions);
float ov_avail_index(int *units_bought_reg,int n_regions);
float tot_pro_cost(float package_fee,int min_pack, int pack_bought);
float fine(int penalty_base,int units_needed, int sum_alloc_units);
int min(int x,int y);
float score(int n_projects,handle *h);

#endif //REPLY_CHALLENGE_MATH_FUNCTIONS_H
