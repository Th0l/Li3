#include "query2.h"

struct q2str {
	int userID; //Id do user
	int totPosts; // Numero total de posts
};

struct passable {
	GSList* info; //GSList que vai guardar a info sobre os N users com mais posts
	int N; //N fornecido á query 2
};

void
slist_free_4(gpointer data)
{
	if(data)
	{
		Q2str fr = (Q2str) data;
		free(fr);
	} 
}

/**
 *Função que vai dar free á estrutura HeadAche com a ajuda da slist_free_4 definida em cima
 */
void
free_q2(HeadAche str)
{
	if(str)
	{
		g_slist_free_full(str->info,slist_free_4);
		free(str);
	}
}

/**
 * Função usada para comparar o numero total de posts, de dois users, para se poder inserir ordenadamente na GSList
 */
gint
g_list_compare_4(gconstpointer a,gconstpointer b)
{
  Q2str aa = (Q2str) a;
  Q2str bb = (Q2str) b;

  return -(aa->totPosts - bb->totPosts);
}
/** 
 *Função usada pela g_tree_foreach() da Query 3 para percorrer a arvore da estrutura dos posts, e que coloca na GSList informação
 *sobre os N users com mais posts
 *@param key gpointer que corresponde ao ID do post usada para meter a sua informação na arvore
 *@param value Estrutura UxPI que contem a informação sobre todos os posts feitos por um certo user
 *@param data Estrutura Passable que contem a informação necessaria para esta função correr
 */
void
query2_traverse(gpointer key,gpointer value,gpointer data)
{
	int lht;
	
	HeadAche inf = (HeadAche) data;
	
	long id = (long) key;

	UxPI info = (UxPI) value;

	if(info != NULL)
	{
		Q2str insert = malloc(sizeof(struct q2str));
		insert->userID = id;
		insert->totPosts = get_post_total(info);
		
		inf->info = g_slist_insert_sorted(inf->info,insert,g_list_compare_4);

		lht = (int) g_slist_length(inf->info);
		if(lht > inf->N)
		{
			inf->info = g_slist_remove(inf->info,g_slist_nth_data(inf->info,11));
		}
	}
}

/** 
 *QUERY 2: Pretende obter o top N utilizadores com maior número de posts de sempre
 *@param com Estrutura Global
 *@param N Quantidade de ID's de users que foi dito para devolver
 *@return Uma LONG_list com os N ID's dos users com mais posts
 */
LONG_list
query2(TAD_community com, int N)
{
	HeadAche pass = malloc(sizeof(struct passable));
	pass->info = NULL;
	pass->N = N;
	int counter;
	Q2str getData;

	g_hash_table_foreach(get_hash_users(com),query2_traverse,pass);

	LONG_list ret = create_list(N+1);

	for(counter = 0 ;counter < N; counter++)
	{
		getData = (Q2str) g_slist_nth_data(pass->info,counter);

		if(getData != NULL)
			set_list(ret,counter,getData->userID);
	}
	
	set_list(ret,counter,(long) NULL);

	free_q2(pass);

	return ret;
}


