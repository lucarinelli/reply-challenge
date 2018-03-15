//
// Created by federica on 15/03/18.
//

#ifndef PROJECT_DATASTRUCTURE_H
#define PROJECT_DATASTRUCTURE_H

typedef struct handle handle;
typedef struct provider provider;
typedef struct project project;
typedef struct region region;

struct handle{
    int V_n_prov, S_n_serv, C_n_coun, P_n_proj;
    provider *providers[];
    project *projects[];
    char **services;
};

struct provider{
    region *regions[];
    int n_regions;
};

struct project{
    int base_penalty;
    int country;//reference intera? change to pointer?
    int units_per_service[];
};

struct region{
    int available_packages;
    float package_unit_cost;
    int units_per_serv[];
    int latency_per_coun[];
};

#endif //PROJECT_DATASTRUCTURE_H
