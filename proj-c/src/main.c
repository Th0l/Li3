
#include <date.h>
#include <stdio.h>
#include "structure.h"

int main(){
/*
 Date d = createDate(1,2,2017);

 printf("Dia: %i\n", get_day(d));
*/ 
  
  TAD_community com = init();

  com = load(com,"/home/thol/Desktop/Universidade/2ºAno-2ªSemestre/Li3-C-Java/Trabalho-C/TestFolder/dump/ubuntu/");

  int lookup = 50;
  Date b = createDate(1,1,2014);
  Date e = createDate(31,1,2014);
  Date b2 = createDate(1,7,2016);
  Date e2 = createDate(31,7,2016);
  char* word = "nautilus";
  int N = 10;

//----------------------------------------------------------------------------//
  printf("<--------------------------------------------------------->\n");
  printf("ID a ser procurado: %d \n",lookup);
  printf("Datas a ser procuradas: Begin: %d-%d-%d. End: %d-%d-%d.\n",get_day(b),get_month(b),get_year(b),get_day(e),get_month(e),get_year(e));
  printf("Palavra a ser procurada: %s\n",word);
  printf("Numero N a ser pedido: %d\n",N);

  printf("<--------------------------------------------------------->\n");
  printf("Query 1\n");
  printf("\n");
//----------------------------------------------------------------------------//

  STR_pair teste1 = info_from_post(com,796430);

  printf("Titulo: %s\n",get_fst_str(teste1) );
  printf("Nome User: %s\n",get_snd_str(teste1) );

//----------------------------------------------------------------------------//
  printf("<--------------------------------------------------------->\n");
  printf("Query 2\n");
  printf("\n");
//----------------------------------------------------------------------------//
  LONG_list teste10 = top_most_active(com, 10);
  int cut;

  for(cut = 0; get_list(teste10,cut) != (long) NULL ;cut++)
  {
    printf("Elemento %d ,ID do User: %ld\n",cut,get_list(teste10,cut));
  }

//----------------------------------------------------------------------------//
  printf("<--------------------------------------------------------->\n");
  printf("Query 3\n");
  printf("\n");
//----------------------------------------------------------------------------//

  LONG_pair teste2 = total_posts(com,b2,e2);

  printf("Numero Perguntas: %ld\n",get_fst_long(teste2) );
  printf("Numero Respostas: %ld\n",get_snd_long(teste2) );

//----------------------------------------------------------------------------//
  printf("<--------------------------------------------------------->\n");
  printf("Query 4\n");
  printf("\n");
//----------------------------------------------------------------------------//
  LONG_list teste5 = questions_with_tag(com,"nautilus",b,e);
  int count;

  for(count = 0; (get_list(teste5,count) != (long) NULL) ;count++)
  {
    printf("Elemento %d ,ID do Post: %ld\n",count,get_list(teste5,count));
  }


//----------------------------------------------------------------------------//
  printf("<--------------------------------------------------------->\n");
  printf("Query 5\n");
  printf("\n");
//----------------------------------------------------------------------------//
  USER teste6 = get_user_info(com,449);
  int ct;

  printf("%s\n",get_bio(teste6));

  long* teste7 = get_10_latest_posts(teste6);

  for(ct=0;ct<10;ct++)
  {
    printf("%ld\n",teste7[ct]);
  }

//----------------------------------------------------------------------------//
  printf("<--------------------------------------------------------->\n");
  printf("Query 6\n");
  printf("\n");
//----------------------------------------------------------------------------//

  LONG_list teste8 = most_voted_answers(com,10,createDate(1,5,2013),createDate(6,5,2013));
  int cout;

  for(cout = 0; get_list(teste8,cout) != (long) NULL ; cout++)
  {
    printf("Elemento %d ,ID do Post: %ld\n",cout,get_list(teste8,cout));  
  }  

//----------------------------------------------------------------------------//
  printf("<--------------------------------------------------------->\n");
  printf("Query 7\n");
  printf("\n");
//----------------------------------------------------------------------------//
  
  LONG_list teste4 = most_answered_questions(com,10,createDate(1,1,2012),createDate(31,12,2012));
  int iterador;

  for(iterador= 0; iterador < 10 ;iterador++)
  {
    printf("Elemento %d ,ID do Post: %ld\n",iterador,get_list(teste4,iterador));
  }

//----------------------------------------------------------------------------//
  printf("<--------------------------------------------------------->\n");
  printf("Query 8\n");
  printf("\n");
//----------------------------------------------------------------------------//

  LONG_list teste3 = contains_word(com,"glib",10);
  int counter;

  for(counter = 0; get_list(teste3,counter) != (long) NULL ;counter++)
  {
    printf("Elemento %d ,ID do Post: %ld\n",counter,get_list(teste3,counter));
  }

//----------------------------------------------------------------------------//
  printf("<--------------------------------------------------------->\n");
  printf("Query 9\n");
  printf("\n");
//----------------------------------------------------------------------------//

  LONG_list teste9 = both_participated(com,87,5691,5);
  int cou;

  for(cou = 0; get_list(teste9,cou) != (long) NULL ;cou++)
  {
    printf("Elemento %d ,ID pergunta em que ambos participaram: %ld\n",cou,get_list(teste9,cou));
  }

//----------------------------------------------------------------------------//
  printf("<--------------------------------------------------------->\n");
  printf("Query 10\n");
  printf("\n");
//----------------------------------------------------------------------------//

  long q10 = better_answer(com,30334);

  printf("A melhor resposta tem o id %ld\n", q10);

//----------------------------------------------------------------------------//
  //printf("\n");
  printf("<--------------------------------------------------------->\n");
  //printf("Teste Hash Users\n");
//----------------------------------------------------------------------------//

return 1;
}




/*
  GHashTable* qtr = get_hash_users(com);
  GArray* test;
  int s;

  if(qtr){
    gpointer xpto = g_hash_table_lookup(get_hash_users(com),GINT_TO_POINTER(lookup));
    UxPI xp = (UxPI) xpto;

    if(xp){
      printf("\n");
      printf("ID do User: %d\n", lookup);
      printf("Numero total de Posts: %d\n", get_post_total(xp));
      test = get_postsID(xp);
      for(int q=0; q<get_post_total(xp); q++){
        s = g_array_index(test, int, q);
        printf( "User participou no post: %d\n", s);
      }
    }
  }

  //----------------------------------------------------------------------------//
  printf("\n");
  printf("<--------------------------------------------------------->\n");
  printf("Teste Hash Posts\n");
//----------------------------------------------------------------------------//
  int r, t;
  GHashTable* gtr = get_hash_posts(com);
  GArray* t1;
  GArray* t2;
  GArray* t3;

  if(gtr){
    gpointer ptxo = g_hash_table_lookup(get_hash_posts(com), GINT_TO_POINTER(look));
    PxUI px = (PxUI) ptxo;
    
    if(px){
      printf("ID do post: %d\n", look);
      printf("Data da pergunta: %d\n", get_date(px));
      printf("Número de respostas ao post: %d\n", get_counter(px));
      t1 = get_answer(px);
      t2 = get_usrID(px);
      t3 = get_datas(px);
      for(t=0; t<get_counter(px); t++){
        r = g_array_index(t1, int, t);
        printf("Id das respostas que participaram no post: %d\n", r);
        r = g_array_index(t2, int, t);
        printf("User que deu essa resposta no post: %d\n", r);
        r = g_array_index(t3, int, t);
        printf("Data da resposta: %d\n", r);
      } 
    }
  }
  

------------------------------------------------------------------------------------------------



  GHashTable* qtr = get_hash_users(com);
  GArray* test;
  int s;

  if(qtr){
    gpointer xpto = g_hash_table_lookup(get_hash_users(com),GINT_TO_POINTER(119));
    UxPI xp = (UxPI) xpto;

    if(xp){
      printf("\n");
      printf("ID do User: %d\n", 119);
      printf("Numero total de Posts: %d\n", get_post_total(xp));
      test = get_quest(xp);
      for(int q=0; q<get_post_total(xp); q++){
        s = g_array_index(test, int, q);
        printf( "User participou na pergunta: %d\n", s);
      }
    }
  }

  if(qtr){
    gpointer xpt = g_hash_table_lookup(get_hash_users(com),GINT_TO_POINTER(7));
    UxPI xd = (UxPI) xpt;

    if(xd){
      printf("\n");
      printf("ID do User: %d\n", 7);
      printf("Numero total de Posts: %d\n", get_post_total(xd));
      test = get_quest(xd);
      for(int x=0; x<get_post_total(xd); x++){
        s = g_array_index(test, int, x);
        printf( "User participou na pergunta: %d\n", s);
      }
    }
  }

  return 1;
}
  */