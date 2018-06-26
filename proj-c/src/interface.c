#include "structure.h"
#include <gmodule.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "interface.h"


TAD_community 
init()
{
	TAD_community com = TAD_create();

	return com;
}


TAD_community
load(TAD_community com,char* dump_path)
{
	com = TAD_load(com,dump_path);

	return com;
}

/*
 * Query 1
*/
STR_pair 
info_from_post(TAD_community com, long id)
{
	STR_pair rep = query1(com,id);

	return rep;
}

/**
 * Query 2
 */
LONG_list 
top_most_active(TAD_community com, int N)
{
	LONG_list rep = query2(com,N);

	return rep;
}

/**
 * Query 3
*/
LONG_pair 
total_posts(TAD_community com, Date begin, Date end)
{
	LONG_pair rep = query3(com,begin,end);

	return rep;
}

/*
 * Query 4
 */
LONG_list
questions_with_tag(TAD_community com, char* tag, Date begin, Date end)
{
	LONG_list rep = query4(com,tag,begin,end);

	return rep;
}

/*
* Query 5
*/
USER
get_user_info(TAD_community com, long id)
{
	USER rep = query5(com, id);

	return rep;
}

/*
 * Query 6
 */
LONG_list
most_voted_answers(TAD_community com, int N, Date begin, Date end)
{
	LONG_list rep = query6(com,N,begin,end);

	return rep;
}

/*
 * Query 7 
*/
LONG_list	
most_answered_questions(TAD_community com, int N, Date begin, Date end)
{
	LONG_list rep = query7(com,N,begin,end);

	return rep;
}

/*
 * Query 8
*/

LONG_list
contains_word(TAD_community com, char* word, int N)
{
	LONG_list rep = query8(com,word,N);

	return rep;
}

/*
 *Query 9
 */
LONG_list
both_participated(TAD_community com, long id1, long id2, int N)
{
	LONG_list rep = query9(com, id1, id2, N);

	return rep;
}

/*
 * Query 10
*/
long 
better_answer(TAD_community com, long id)
{
	long rep = query10(com,id);

	return rep;
}

/*
 * Função clean
*/
TAD_community
clean(TAD_community com)
{
	com = TAD_destroy(com);

	return com;
}
