#include "query5.h"

struct dataANDid
{
	long id; // id do post
	int data; //data da publicação
};

void
free_q5(gpointer data)
{
	if(data != NULL)
	{
		dAi dt = (dAi) data;
		free(dt);
	}
}

/**
 * Função usada pela g_slist_insert_sorted da query 5 para inserir os elementos do mais recente para o mais antigo na GSList
 */
gint
compara_data(gconstpointer a,gconstpointer b)
{
	dAi aa = (dAi) a;
	dAi bb = (dAi) b;

	return -(aa->data - bb->data);
}

/** 
 *QUERY 5: Dado um ID de utilizador, devolver a informação do seu perfil (short bio) e os IDs dos seus 10 últimos posts
 *@param com Estrutura Global
 *@param id ID do utilizador a procurar
 *@return Uma LONG_list com os N ID's dos users com mais posts
 */
USER
query5 (TAD_community com, long id)
{
	USRP user;

	GSList* pst_id = NULL;

	char* bio;

	int i,lht;

	long fid[10];

	dAi getID;

	gpointer p = g_tree_lookup(get_users(com),GINT_TO_POINTER(id));

	if(p!=NULL)
	{	
		
		user = (USRP) p;

		bio = get_user_bio(user);

		
		gpointer xx = g_hash_table_lookup(get_hash_users(com), GINT_TO_POINTER(id));

		if(xx!=NULL)
		{
			UxPI uxPI = (UxPI) xx;
			for(i=0; i<get_post_total(uxPI);i++)
			{	
				dAi insert = malloc(sizeof(struct dataANDid));
				insert->id = g_array_index(get_postsID(uxPI), int, i);//pid;
				insert->data = g_array_index(get_dat(uxPI), int, i);//dt;

				pst_id = g_slist_insert_sorted(pst_id, insert, compara_data);

				lht = (int) g_slist_length(pst_id);
				if(lht > 10)
				{
					pst_id = g_slist_remove(pst_id,g_slist_nth_data(pst_id,lht-1));
				}
			}
		}

		int length = (int) g_slist_length(pst_id);

		for(i=0; ((i<length) && (i<10)); i++)
		{
			getID = (dAi) g_slist_nth_data(pst_id,i);

			fid[i] = getID->id;
		}

		for(; i<10;i++)
		{
			fid[i] = -3;
		}

		USER f = create_user(bio, fid);

		g_slist_free_full(pst_id,free_q5);

		return f;
	}

	return NULL;
}