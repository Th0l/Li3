#include "query6.h"

/**
 *Estrutura Q3str usada como suporte para a Query 3
 */
struct q6str {
	int dBegin; //inicio do intervalo de tempo
	int dEnd; //fim do intervalo de tempo
	int N; //numero de respostas pedidas
	GSList *info; //GSList que vai guardar a informação das N respostas que vão ser devolvidas
};

/*
 *Estrutura que vai ser colocado nos vários nodos da GSList usada, com o id de uma resposta e o seu score
 */
struct idANDscore {
	long id;// id da resposta
	int score;//score da resposta
};

void
slist_free_3(gpointer data)
{
	if(data)
	{
		iAs fr = (iAs) data;
		free(fr);
	} 
}

/*
 *Função que vai dar free á estrutura Q6str com a ajuda da slist_free_3 definida em cima
 */
void
free_q6(Q6str str)
{
	if(str)
	{
		g_slist_free_full(str->info,slist_free_3);
		free(str);
	}
}

/**
 *Função usada pela g_list_insert para ordenar os posts pelo score, do menor para o maior
 */
gint
g_list_compare_3(gconstpointer a,gconstpointer b)
{
  iAs aa = (iAs) a;
  iAs bb = (iAs) b;

  return -(aa->score - bb->score);
}

/**
 *Função usada pela g_tree_foreach() da QUERY 6 que vai percorrer arvore inteira e colocar numa lista ligada da glib, 
 *o ID dos N posts com mais votos
 *@param key gpointer que corresponde ao ID do post usada para meter a sua informação na arvore
 *@param value gpointer que corresponde a uma estrutura PSTI que contem a informação necessária sobre os Posts
 *@param data gpointer que corresponde a uma estrutura Q6str que contem a informação necessária para o funcionamento da função
 *@return FALSE, para signalizar a foreach, para ñ parar de percorrer a arvore
 */
gboolean
query6_traverse(gpointer key,gpointer value,gpointer data)
{
	int lht;

	Q6str info = (Q6str) data;

	PSTI post = (PSTI) value;

	if(get_post_type(post) == 2)
	{
		if((get_post_ccTime(post) >= info->dBegin) && (get_post_ccTime(post) <= info->dEnd))
		{
			iAs insert = malloc(sizeof(struct idANDscore));
			insert->id = get_post_id(post);
			insert->score = get_post_score(post);

			info->info = g_slist_insert_sorted(info->info,insert,g_list_compare_3);
			
			lht = (int) g_slist_length(info->info);
			if(lht > info->N)
			{
			info->info = g_slist_remove(info->info,g_slist_nth_data(info->info,lht-1));
			}
		}
	}	
	
	return FALSE;
}

/** 
 *QUERY 6: Dado um intervalo de tempo arbitrário, devolver os IDs das N respostas com mais votos
 *@param com Estrutura Global
 *@param N numero de Id's que se quer devolver
 *@param begin Data inicial que se vai procurar
 *@param end Data final que se vai procurar
 *@return Uma LONG_list com os N id's dos posts mais recentes, se ouver menos do q N posts, os espaços vazios são preenchidos com "-3"
 */
LONG_list
query6(TAD_community com,int N,Date begin,Date end)
{
	Q6str pass = malloc(sizeof(struct q6str));
	iAs getData;
	int cBegin = ((get_year(begin)*10000)+(get_month(begin)*100)+(get_day(begin)));
	int cEnd = ((get_year(end)*10000)+(get_month(end)*100)+(get_day(end)));

	int counter,lht,it;

	pass->dBegin = cBegin;
	pass->dEnd = cEnd;
	pass->N = N;
	pass->info = NULL;

	g_tree_foreach(get_posts(com),query6_traverse,pass);	

	lht = (int) g_slist_length(pass->info);

	if(lht >= N)
		it = N;
	else
		it = lht;

	LONG_list ret = create_list(it + 1);

	for(counter = 0 ;counter < it; counter++)
	{
		getData = (iAs) g_slist_nth_data(pass->info,counter);

		if(getData != NULL)
			set_list(ret,counter,getData->id);
	}
	
	set_list(ret,counter,(long) NULL);

	free_q6(pass);

	return ret;
}