//
// Created by Zehao Jin on 18/03/2018.
//

#ifndef EV_PB_RPC_LOG_H
#define EV_PB_RPC_LOG_H

#include<cstdio>

#define log(format, args...) fprintf(stdout, "%s:%d " format "\n",  __FILE__, __LINE__, ##args)

#endif //EV_PB_RPC_LOG_H
