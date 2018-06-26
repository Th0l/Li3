#include "query7.h"

struct q7str{
	int fim;//fim do intervalo de tempo
	int inicio;//inicio do intervalo de tempo
	int N;//numero de ID's a devolver
	GSList *info;//GSList que vai conter os id's dos posts a devolver
};

struct countANDpost
{
	long id;//id do post
	int count;//numero de respostas dentro do intervalo de tempo
};

void
free_slist(gpointer data)
{
	if(data != NULL)
	{
		cAp dt = (cAp) data;
		free(dt);
	}
}

void
free_q7(Q7str data)
{
	if(data != NULL)
	{
		g_slist_free_full(data->info,free_slist);
		free(data);
	}
}

/**
 *Função q testa se um post esta dentro do intervalo de tempo definido
 */
int
limite(int x, int i, int f) //ver se data x ocorre entre i e f
{
	int fx, ix;
	fx = f-x;
	ix = i-x;
	if(fx>=0 && ix<=0)
	{
		return 1;
	}
	return 0;
}

/**
 *Função usada para comparar dois contadores de respostas, usada para ordenar a GSList
 */
gint
g_l_compare(gconstpointer a,gconstpointer b)
{
  cAp aa = (cAp) a;
  cAp bb = (cAp) b;

  return -(aa->count - bb->count);
}

/** 
 *Função usada pela g_hash_table_foreach() da Query 7 para colocar os id's dos posts com mais respostas dentro 
 *da GSList ordenadamente
 *@param key gpointer que corresponde ao ID do post usada para meter a sua informação na hash
 *@param value Estrutura PxUI que contem a informação sobre todos os users que participaram num certo post
 *@param data Estrutura q7str que contem a informação necessaria para esta função correr
 */
gboolean
travessia(gpointer key, gpointer value, gpointer data)
{
	Q7str info = (Q7str) data;

	PxUI post = (PxUI) value;

	int i, cont=0, ti2,lht;

	GArray* t2;	


	if( limite(get_date(post), info->inicio, info->fim) ==1 )//se está dentro das datas pedidas
	{
		t2 = get_datas(post);
		for(i=0; i<get_counter(post)-1; i++)
		{	
			ti2 = g_array_index(t2, int, i);
			if(limite(ti2, info->inicio, info->fim)==1)
			{	
				cont+=1;
			}

		}		
		cAp insert = malloc(sizeof(struct countANDpost));
		insert->id = (long) key;
		insert->count = cont;
		info->info = g_slist_insert_sorted(info->info, insert, g_l_compare);
		
		lht = (int) g_slist_length(info->info);
		if(lht > info->N)
		{
			info->info = g_slist_remove(info->info,g_slist_nth_data(info->info,lht-1));
		}
	}	

	return FALSE;
}

/** 
 *QUERY 7: Dado um intervalo de tempo arbitrário, devolver as IDs das N perguntas com mais respostas
 *@param com Estrutura Global
 *@param N numero de Id's que se quer devolver
 *@param begin Data inicial do intervalo de tempo
 *@param end Data final do intervalo de tempo
 *@return Uma LONG_list com os N ID's das perguntas com mais respostas, estas respostas tb se encontram dentro do tempo limite 
 *definido, se ouver menos do q N posts, os espaços vazios são preenchidos com "-3"
 */
LONG_list
query7(TAD_community com,int N,Date begin,Date end)
{
	Q7str data = malloc(sizeof(struct q7str));
	int iterador;
	int it;
	cAp getID;

	data->fim = ((get_year(end)*10000)+(get_month(end)*100)+(get_day(end)));
	data->inicio = ((get_year(begin)*10000)+(get_month(begin)*100)+(get_day(begin)));
	data->info = NULL;
	data->N = N;

	g_hash_table_foreach_remove(get_hash_posts(com), travessia , data);

	int ls = (int) g_slist_length(data->info);

	if(N<ls)
	{
		it=N;
	}
	else
	{
		it=ls;
	}

	LONG_list ret = create_list(it + 1);

	for(iterador=0; iterador<it; iterador++)
	{
		getID = (cAp) g_slist_nth_data(data->info,iterador);

		set_list(ret,iterador,getID->id);
	}

	set_list(ret,iterador,(long) NULL);

	free_q7(data);

	return ret;

}