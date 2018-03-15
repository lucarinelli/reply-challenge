//
// Created by federica on 15/03/18.
//

#ifndef REPLY_CHALLENGE_MATH_FUNCTIONS_H
#define REPLY_CHALLENGE_MATH_FUNCTIONS_H

#include "datastructure.h"
#include <stdlib.h>

float score(handle *h, order *o, project *p);
float avg_pr_latency(handle *h, project *p, order *o);
float ov_avail(handle *h, project *p, order *o);
float tot_pro_cost(handle *h, project *p, order *o);
float fine(handle *h, project *p, order *o);
int min(int x,int y);

#endif //REPLY_CHALLENGE_MATH_FUNCTIONS_H
