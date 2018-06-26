#ifndef __Q6__
#define __Q6__

#include "structure.h"

typedef struct q6str *Q6str;

typedef struct idANDscore *iAs;

LONG_list query6(TAD_community com,int N,Date begin,Date end);

#endif