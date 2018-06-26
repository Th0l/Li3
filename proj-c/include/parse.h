#ifndef __PARSE__
#define __PARSE__

#include "structure.h"

GTree* parse_users(char* dump_path);

GTree* parse_posts(char* dump_path);

GHashTable* parse_UInfo(char* dump_path);

GHashTable* parse_PInfo(char* dump_path);

GHashTable* parse_Tag(char* dump_path);

#endif