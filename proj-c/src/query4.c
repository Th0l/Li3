#include "query4.h"

/**
 *Estrutura usada para a query4 poder funcionar 
 */
struct q4str {
	int dBegin; //inicio do intervalo de tempo
	int dEnd; //fim do intervalo de tempo
	char* wr; //tag fornecida á query 4
	GSList *info; //GSList que vai conter os posts que contêm a tag pedida
};

/**
 *Estrutura que vai ser colocado nos vários nodos da GSList usada, com o id de um post e a sua data
 */
struct idTime {
	long id; //id do post
	int time; //data de publicação do psot
};

void
slist_free_2(gpointer data)
{
	if(data)
	{
		iDt fr = (iDt) data;
		free(fr);
	} 
}

/**
 *Função que vai dar free á estrutura Q4str com a ajuda da slist_free_2 definida em cima
 */
void
free_q4(Q4str str)
{
	if(str)
	{
		free(str->wr);
		g_slist_free_full(str->info,slist_free_2);
		free(str);
	}
}

/**
 *Função usada pela g_list_insert para ordenar os posts pela data em ordem do mais antigo para o mais recent
 */
gint
g_list_compare_2(gconstpointer a,gconstpointer b)
{
  iDt aa = (iDt) a;
  iDt bb = (iDt) b;

  return (aa->time - bb->time);
}

/**
 *Função usada pela g_tree_foreach() da QUERY 4 que vai percorrer arvore inteira e colocar numa lista ligada da glib, o ID de todos os posts que contêm a tag pedida
 *@param key gpointer que corresponde ao ID do post usada para meter a sua informação na arvore
 *@param value gpointer que corresponde a uma estrutura PSTI que contem a informação necessária sobre os Posts
 *@param data gpointer que corresponde a uma estrutura Q4str que contem a informação adicional que era necessário para o funcionamento desta função
 *@return FALSE, para signalizar a foreach, para ñ parar de percorrer a arvore
 */
gboolean
query4_traverse(gpointer key,gpointer value,gpointer data)
{
	Q4str info = (Q4str) data;

	PSTI post = (PSTI) value;

	if((get_post_ccTime(post) >= info->dBegin) && (get_post_ccTime(post) <= info->dEnd))
	{
		if(strstr(get_post_tags(post),info->wr) != NULL)
		{
			iDt insert = malloc(sizeof(struct idTime));
			insert->id = get_post_id(post);
			insert->time = get_post_ccTime(post);

			info->info = g_slist_insert_sorted(info->info,insert,g_list_compare_2);
		}
	}

	return FALSE;
}

/** 
 *QUERY 4: Dado um intervalo de tempo arbitrário, retornar todas as perguntas contendo uma determinada tag.
 *@param com Estrutura Global
 *@param tag Tag que ser quer procurar
 *@param begin Data inicial entre a qual se vai procurar
 *@param end Data final entre a qual se vai procurar
 *@return Uma LONG_list com os id's dos posts que contêm a tag pedida 
 */
LONG_list 
query4(TAD_community com, char* tag, Date begin, Date end)
{
	Q4str pass = malloc(sizeof(struct q4str));
	iDt getData;

	int cBegin = ((get_year(begin)*10000)+(get_month(begin)*100)+(get_day(begin)));
	int cEnd = ((get_year(end)*10000)+(get_month(end)*100)+(get_day(end)));

	int counter,lht;

	char* left = "<"; char* right = ">";

	pass->dBegin = cBegin;
	pass->dEnd = cEnd;

	pass->wr = malloc(strlen(tag) + strlen(left) + strlen(right) + 1);
	strcpy(pass->wr,left);
	strcat(pass->wr,tag);
	strcat(pass->wr,right);
	
	pass->info = NULL;

	g_tree_foreach(get_posts(com),query4_traverse,pass);

	pass->info = g_slist_reverse(pass->info);

	lht = (int) g_slist_length(pass->info);

	LONG_list ret = create_list(lht + 1);

	for(counter = 0 ;counter < lht; counter++)
	{
		getData = (iDt) g_slist_nth_data(pass->info,counter);

		if(getData != NULL)
			set_list(ret,counter,getData->id);
	}

	set_list(ret,counter,(long) NULL);

	free_q4(pass);

	return ret;
}
