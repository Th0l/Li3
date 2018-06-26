#ifndef __STRUCTURE__
#define __STRUCTURE__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <glib.h>

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "interface.h"
#include "common.h"
#include "user.h"
#include "timeANDvotes.h"
#include "query1_3.h"
#include "query2.h"
#include "query4.h"
#include "query5.h"
#include "query6.h"
#include "query7.h"
#include "query8.h"
#include "query9.h"
#include "query10.h"
#include "parse.h"

#include "pair.h"
#include "date.h"


typedef struct usrXpost_info *UxPI;
typedef struct postXusr_info *PxUI;
typedef struct usr_posts *USRP;
typedef struct post_Information *PSTI;
typedef struct tag_Info *TI;


TAD_community TAD_create();
TAD_community TAD_load(TAD_community com,char* dump_path);
TAD_community TAD_destroy(TAD_community com);

USRP new_user(long id,int rep,char* bio,char* nome);
PSTI new_post(int id,int uid,int type,int parent,int score,int comm,char* titu,char* tags,int data);
UxPI new_UxPI(int id, GArray *pID, GArray *da, GArray *q, GArray *ta);
PxUI new_PxUI(int c, int d,  GArray *ans, GArray *uID, GArray* da);
TI new_TI(long c);

GTree* get_posts(TAD_community com);
GTree* get_users(TAD_community com);
GHashTable* get_hash_users(TAD_community com);
GHashTable* get_hash_posts(TAD_community com);
GHashTable* get_hash_tag(TAD_community com);

int get_post_id(PSTI post);
int get_post_user(PSTI post);
int get_post_type(PSTI post);
int get_post_parent(PSTI post);
int get_post_score(PSTI post);
int get_post_comm(PSTI post);
char* get_post_title(PSTI post);
char* get_post_tags(PSTI post);
int get_post_ccTime(PSTI post);

long get_user_id(USRP user);
int get_user_rep(USRP user);
char* get_user_bio(USRP user);
char* get_user_name(USRP user);

int get_post_total(UxPI user);
GArray* get_postsID(UxPI user);
GArray* get_dat(UxPI user); 
GArray* get_quest(UxPI);
GArray* get_tags(UxPI user);

int get_counter(PxUI user);
int get_date(PxUI user);
GArray* get_answer(PxUI user);
GArray* get_usrID(PxUI user);
GArray* get_datas(PxUI user);

long get_id(TI user);

#endif