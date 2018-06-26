#include "query8.h"

/*
 *Estrutura usada para a query8 poder funcionar 
 */
struct q8str {
	char* wr;//Palavra pedida
	int N;//o numero total de ID's a devolver
	GSList *info;//GSList que vai guardar os ID's dos posts a devolver
};

/*
 *Estrutura que vai ser colocado nos vários nodos da GSList usada, com o id de um post e a sua data
 */
struct idANDtime {
	long id;//ID do post
	int time;//Data de publicação do post
};


void
slist_free(gpointer data)
{
	if(data)
	{
		iAt fr = (iAt) data;
		free(fr);
	} 
}

/*
 *Função que vai dar free á estrutura Q8str com a ajuda da slist_free definida em cima
 */
void
free_q8(Q8str str)
{
	if(str)
	{
		free(str->wr);
		g_slist_free_full(str->info,slist_free);
		free(str);
	}
}

int 
aux(char* str,char* wr)
{
	int i = 0;

	while(str[i] != '\0')
	{
		if(str[i] != wr[i]){return 0;}
		i++;
	}

	if(wr[i] != '\0'){return 0;}
	
	return 1;
}

/**
 *Função que vai verificar se uma palavra está contida num titulo com a ajuda da função "aux" definida em cima
 */
int
contains(char* str, char* wr)
{
	char* print;
	const char *delet = " !./;,:-_º+*-";
	
	char *title = malloc(strlen(str) + 1);
	char *word = malloc(strlen(wr) + 1);

	strcpy(title,str);
	strcpy(word,wr);

	if(title != NULL)
		print = strtok(title,delet);

	while(print != NULL)
	{
		if(aux(print,word)){return 1;}

		print = strtok(NULL,delet);
	}

	return 0;

}
/**
 *Função usada pela g_list_insert para ordenar os posts pela data em ordem do mais antigo para o mais recent
 */
gint
g_list_compare(gconstpointer a,gconstpointer b)
{
  iAt aa = (iAt) a;
  iAt bb = (iAt) b;

  return -(aa->time - bb->time);
}

/**
 *Função usada pela g_tree_foreach() da QUERY 8 que vai percorrer arvore inteira e colocar numa lista ligada da glib, o ID de todos os posts que contêm a palavra a ser procurada no seu titulo
 *@param key gpointer que corresponde ao ID do post usada para meter a sua informação na arvore
 *@param value gpointer que corresponde a uma estrutura PSTI que contem a informação necessária sobre os Posts
 *@param data gpointer que corresponde a uma estrutura Q8str que contem a informação adicional que era necessário para o funcionamento desta função
 *@return FALSE, para signalizar a foreach, para ñ parar de percorrer a arvore
 */
gboolean
query8_traverse(gpointer key,gpointer value,gpointer data)
{
	int lht;

	Q8str info = (Q8str) data;

	PSTI post = (PSTI) value;

	if(get_post_type(post) == 1)
	{
		if(contains(get_post_title(post),info->wr))
		{
			iAt insert = malloc(sizeof(struct idANDtime));
			insert->id = get_post_id(post);
			insert->time = get_post_ccTime(post);

			info->info = g_slist_insert_sorted(info->info,insert,g_list_compare);

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
 *QUERY 8: Dado uma palavra, devolver uma lista com os IDs de N perguntas cujos tı́tulos a contenham, ordenados por cronologia inversa
 *@param com Estrutura Global
 *@param word Palavra pela qual se quer procurar
 *@param N O numero total de id's a devolver
 *@return Uma LONG_list com os N id's dos posts mais recentes, caso a palavra em questão tenha aparecido em menos de N posts, as restantes posições da LONG_list vão estar preenchidas com "-2"
 */
LONG_list
query8(TAD_community com, char* word, int N)
{
	Q8str pass = malloc(sizeof(struct q8str));
	int counter,it;
	iAt getData;

	pass->wr = malloc(strlen(word) + 1);
	strcpy(pass->wr,word);
	pass->info = NULL;
	pass->N = N;

	g_tree_foreach(get_posts(com),query8_traverse,pass);

	int lht = (int) g_slist_length(pass->info);

	if(lht >= N)
		it = N;
	else
		it = lht;

	LONG_list ret = create_list(it + 1);

	for(counter = 0 ;counter < it; counter++)
	{
		getData = (iAt) g_slist_nth_data(pass->info,counter);

		if(getData != NULL)
			set_list(ret,counter,getData->id);
	}

	set_list(ret,counter,(long) NULL);

	free_q8(pass);

	return ret;
}
