#include "query1_3.h"

/**
 *Estrutura Q3str usada como suporte para a Query 3
 */
struct q3str {
  int dBegin;
  int dEnd;
  int cRep;
  int cPer;
};

/** 
 *QUERY 1: Dado o identificador de um post, a função deve retornar o tı́tulo do post e o nome de utilizador do autor
 *@param com Estrutura Global
 *@param id ID do post que se quer procurar
 *@return Um STR_pair com o titulo do post com o ID fornecido ou pai da resposta, e o UserName do utilizador que fez essa pergunta
 */
STR_pair 
query1(TAD_community com,long id)
{
	PSTI post;

	USRP user;

	char* nome; char* titulo;

	gpointer p = g_tree_lookup(get_posts(com),GINT_TO_POINTER(id));

	if(p)
	{
		post = (PSTI) p;

		if(get_post_type(post) == 1)
		{
			titulo = get_post_title(post);

			gpointer u = g_tree_lookup(get_users(com),GINT_TO_POINTER(get_post_user(post)));

			if(u)
			{
				user = (USRP) u;
                
                nome = get_user_name(user);
			}
			
			else{printf("Error looking up ID in user related parsed tree\n");}
		}

		else
		{
			p = g_tree_lookup(get_posts(com),GINT_TO_POINTER(get_post_parent(post)));

			if(p)
			{
				post = (PSTI) p;

				titulo = get_post_title(post);

				gpointer u = g_tree_lookup(get_users(com),GINT_TO_POINTER(get_post_user(post)));

				if(u)
				{
					user = (USRP) u;
                
                	nome = get_user_name(user);
				}

				else{printf("Error looking up ID in user related parsed tree\n");}

			}

			else{printf("Error looking up father ID in post related parsed tree\n");}
		}

		STR_pair resposta = create_str_pair(titulo,nome);

		return resposta;
	}

	else{printf("Error looking up ID in post related parsed tree \n");}
	
	return NULL;
}	



/** 
 *Função usada pela g_tree_foreach() da Query 3 para percorrer arvore da estrutura dos posts que vai contabilizar todas 
 *as ocurrencias de perguntas e respostas presentes
 *@param key gpointer que corresponde ao ID do post usada para meter a sua informação na arvore
 *@param value Estrutura PSTI dos posts que contem a informação de um dado post
 *@param data Estrutura Q3str que contem a informação necessaria para esta função correr
 *@return FALSE, para signalizar a foreach, para ñ parar de percorrer a arvore
 */
gboolean
query3_traverse(gpointer key, gpointer value, gpointer data)
{
	Q3str info = (Q3str) data;

	PSTI post = (PSTI) value;

	if((get_post_ccTime(post) >= info->dBegin) && (get_post_ccTime(post) <= info->dEnd))
	{
		if(get_post_type(post) == 1){info->cPer += 1;}

		if(get_post_type(post) == 2){info->cRep += 1;}
	}	

	return FALSE;
}

/** 
 *QUERY 3: Dado um intervalo de tempo 4 arbitrário, obter o número total de posts
 *@param com Estrutura Global
 *@param begin Data inicial que se vai procurar
 *@param end Data final que se vai procurar
 *@return Um LONG_pair com o numero total de perguntas e repostas, o numero total de perguntas vai tar no primeiro 
 *elemento da LONG_pair, e o numero total de respostas vai estar no segundo elemento do LONG_pair
 */
LONG_pair 
query3(TAD_community com, Date begin, Date end)
{
	int cBegin = ((get_year(begin)*10000)+(get_month(begin)*100)+(get_day(begin)));
	int cEnd = ((get_year(end)*10000)+(get_month(end)*100)+(get_day(end)));

	Q3str pass = malloc(sizeof(struct q3str));
	
	pass->dBegin = cBegin;
	pass->dEnd = cEnd;
	pass->cRep = 0;
	pass->cPer = 0;

	g_tree_foreach(get_posts(com),query3_traverse,pass);

	LONG_pair ret = create_long_pair(pass->cPer,pass->cRep);

	return ret;
}










