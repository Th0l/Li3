#include "query9.h"

struct datANDid
{
	long id; //id do post
	int data; //data da sua publicação
};

void
free_q9(gpointer data)
{
	if(data != NULL)
	{
		DAI dt = (DAI) data;
		free(dt);
	}
}

/**
 *Função que vai comparar as datas dos posts, usada pela g_slist_insert_sorted()
 */
gint
compara_date(gconstpointer a,gconstpointer b)
{
	DAI aa = (DAI) a;
	DAI bb = (DAI) b;

	return(aa->data - bb->data);
}

/** 
 *QUERY 9: Dados os IDs de dois utilizadores, devolver as últimas N perguntas em que participaram os dois utilizadores
 *@param com Estrutura Global
 *@param id1 ID de um dos users
 *@param id2 ID de um dos users
 *@param N numero de posts que se pretende ser devolvido
 *@return Uma LONG_list com os N id's dos posts mais recentes, em q ambos users participaram, 
 *se ouver menos do q N posts, os espaços vazios são preenchidos com "-3"
 */
LONG_list
query9(TAD_community com, long id1, long id2, int N)
{
	int z,zd,i,zz,x,it, data;

	gpointer p1 = g_hash_table_lookup(get_hash_users(com), GINT_TO_POINTER(id1));
	gpointer p2 = g_hash_table_lookup(get_hash_users(com), GINT_TO_POINTER(id2));

	GSList* pst_id = NULL;
	GSList* check = NULL;

	DAI getID;

	if(p1!=NULL && p2!=NULL)
	{
		UxPI hp1 = (UxPI) p1;
		UxPI hp2 = (UxPI) p2;

	int th1 = get_post_total(hp1);
	int th2 = get_post_total(hp2);

	GArray* ah1 = get_quest(hp1);
	GArray* dh1 = get_dat(hp1);
	GArray* ah2 = get_quest(hp2);
	
	for(i = 0; i<th1; i++)
	{
		z = g_array_index(ah1, int, i);
		zd = g_array_index(dh1, int, i);
		for(x = 0; x<th2; x++)
		{
			zz = g_array_index(ah2, int, x);
			if(z==zz)//Se ambos participaram na mesma pergunta
			{
				gpointer p3 = g_hash_table_lookup(get_hash_posts(com), GINT_TO_POINTER(z));
				if(p3!=NULL)
				{
					PxUI dat = (PxUI) p3;
					data = get_date(dat);
				}
				else
				{
					data = zd;
				}
				if(g_slist_find(check, GINT_TO_POINTER(z))==NULL){
					DAI insert = malloc(sizeof(struct datANDid));
					insert->id = z;
					insert->data = data;

					check = g_slist_append(check, GINT_TO_POINTER(z));
					pst_id = g_slist_insert_sorted(pst_id, insert, compara_date);
				}

				break;
			}
		}
	}

	pst_id = g_slist_reverse(pst_id);

	int length = (int) g_slist_length(pst_id);

	if(N<length)
	{
		it=N;
	}
	else
	{
		it=length;
	}

	LONG_list ret = create_list(it + 1);

	for(i=0; (i<it); i++)
	{
		getID = (DAI) g_slist_nth_data(pst_id,i);

		set_list(ret, i, getID->id);
	}

	set_list(ret, i, (long) NULL);

	g_slist_free_full(pst_id,free_q9);

	return ret;
	}

	else
	{
		return NULL;
	}

}