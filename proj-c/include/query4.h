#ifndef __Q4__
#define __Q4__

#include "structure.h"

typedef struct q4str *Q4str; 
typedef struct idTime *iDt;

LONG_list query4(TAD_community com, char* tag, Date begin, Date end);

#endif