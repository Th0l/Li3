#include "query10.h"

/*
 *Função que vai calcular o score de uma resposta
 */
float
function(int score,int reputation,int comments)
{
	float ret = (float) ((score*0.65) + (reputation*0.25) + (comments*0.1));

	return ret;
}

/** 
 *QUERY 10: Dado o ID de uma pergunta, obter a melhor resposta
 *@param com Estrutura Global
 *@param id É o id da Pergunta da qual se quer saber a melhor resposta
 *@return Um long com o id da melhor resposta
 */
long
query10(TAD_community com,long id)
{
	GHashTable* hash = get_hash_posts(com);
	GTree* tree1 = get_posts(com);
	GTree* tree2 = get_users(com);
	GArray* reps;
	float top,comp;
	long topID,compID;
	int i,t,idd,comm,sc,usID,rep;
	top = 0;

	gpointer hs = g_hash_table_lookup(hash,GINT_TO_POINTER(id));

	if(hs != NULL)
	{
		PxUI hsh = (PxUI) hs;
		if(hsh != NULL)
		{
			reps = get_answer(hsh);
			
			if (reps->len == 0)
				return -1;

			t = get_counter(hsh);
				
			for(i = 0 ;i < t; i++)
			{
				idd = g_array_index(reps,int,i);

				gpointer pst = g_tree_lookup(tree1,GINT_TO_POINTER(idd));

				PSTI post = (PSTI) pst;

				if(post != NULL)
				{
					comm = get_post_comm(post); 
						sc = get_post_score(post); 
							usID = get_post_user(post);

					gpointer usr = g_tree_lookup(tree2,GINT_TO_POINTER(usID));
					USRP user = (USRP) usr;

					if(user != NULL)
					{
						rep = get_user_rep(user);

						comp = function(sc,rep,comm);
						compID = idd;

						if(comp > top)
						{
							top = comp;
							topID = compID;
						}
					}
				}
			}
		}
	}

	else
		return -1;

	return topID;
}