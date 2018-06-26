/*
	Ficheiro .c que contem a definição das funções que 
	vão preeencher as diferentes estruturas usadas para
	guardar a informação obtida dos ficheiros .xml 
*/

#include "structure.h"

//Estrutura que vai guardar o id de uma certa tag
typedef struct tag_Info {
	long id;
}tag_Info;

//Estrutura que vai guardar o numero de posts totais e o id desses posts relativos a um certo user
typedef struct usrXpost_info {
	int post_total; //Numero total de posts 
	GArray *postsID; //Id dos posts
	GArray *datas;
	GArray *questID;
	GArray *tags;
}usrXpost_info;

//Estrutura que vai guardar o numero de respostsa totais de 
typedef struct postXusr_info {
	int dateP;
	int count;//Contador de números de elementos dos arrays
	GArray *answer;
	GArray *usrID;
	GArray *datas;
}postXusr_info;

//Estrutura que vai guardar informação relacionada com o id do user
typedef struct usr_posts {
   long usrID;
   int reputation;
   char* bio;
   char* usrName;
}usr_posts;

//Estrutura que vai guardar a diversa informação relacionada com os posts que é necessaria
typedef struct post_Information {
   int postID;
   int pUsrID;
   int pType;
   
   int parentID; /* Só a usar se for uma resposta, corresponde ao id da pergunta ao qual esta resposta pertence */
   int score;
   int comments;
   
   char* titulo; /*Só a usar se for uma pergunta */
   char* tags; /*Array vai conter todas as tags pertencentes a este post, só a usar se for uma Pergunta */
	
   int dataNumber;

}post_Information;

//Estrutura Global
typedef struct TCD_community
{
	GTree *treePosts;
	GTree *treeUsers;
	GHashTable *userXinfo;
	GHashTable *infoXuser;
	GHashTable *tagInfo;

}TCD_community;

/**
 * Funções usadas para obter a diferente informação pertencente as estruturas definidas aqui
*/

TAD_community
TAD_create()
{
	TAD_community com = (TAD_community) malloc(sizeof(struct TCD_community));

	return com;
}

TAD_community
TAD_load(TAD_community com,char* dump_path)
{
	com->treePosts = parse_posts(dump_path);

	com->treeUsers = parse_users(dump_path);

	com->userXinfo = parse_UInfo(dump_path);

	com->infoXuser = parse_PInfo(dump_path);

	com->tagInfo = parse_Tag(dump_path);

	return com;
}

TAD_community
TAD_destroy(TAD_community com)
{
	g_tree_destroy(com->treePosts);
	free(com->treePosts);

	g_tree_destroy(com->treeUsers);
	free(com->treeUsers);

	g_hash_table_destroy(com->userXinfo);
	free(com->userXinfo);

	g_hash_table_destroy(com->infoXuser);
	free(com->infoXuser);

	g_hash_table_destroy(com->tagInfo);
	free(com->tagInfo);

	return com;
}

//Função que recebe parametros das parses e cria uma nova estrutura USRP
USRP
new_user(long id,int rep,char* bio,char* nome)
{
	USRP fullUser = (USRP) malloc(sizeof(struct usr_posts));

	fullUser->usrID = id;
	fullUser->reputation = rep;
	fullUser->bio = bio;
	fullUser->usrName = nome;

	return fullUser;
}

//Função que recebe parametros das parses e cria uma nova estrutura PSTI
PSTI
new_post(int id,int uid,int type,int parent,int score,int comm,char* titu,char* tags,int data)
{
	PSTI fullPost = (PSTI) malloc(sizeof(struct post_Information));	

	fullPost->postID = id;
	fullPost->pUsrID = uid;
	fullPost->pType = type;
	fullPost->parentID = parent;
	fullPost->score = score;
	fullPost->comments = comm;
	fullPost->titulo = titu;
	fullPost->tags = tags;
	fullPost->dataNumber = data;

	return fullPost;
}

//Função que recebe parametros das parses e cria uma nova estrutura UxPI
UxPI
new_UxPI(int id, GArray *pID, GArray *da, GArray *q, GArray *ta)
{
	UxPI fullPost = (UxPI) malloc(sizeof(struct usrXpost_info));
	fullPost->postsID = (GArray*) malloc(sizeof(struct GArray*));
	fullPost->datas = (GArray*) malloc(sizeof(struct GArray*));
	fullPost->questID = (GArray*) malloc(sizeof(struct GArray*));
	fullPost->tags = (GArray*) malloc(sizeof(struct GArray*));

	fullPost->post_total = id + 1;
	fullPost->postsID = pID;
	fullPost->datas = da;
	fullPost->questID = q;
	fullPost->tags = ta;

	return fullPost;
}

//Função que recebe parametros das parses e cria uma nova estrutura PxUI
PxUI
new_PxUI(int c, int d,  GArray *ans, GArray *uID, GArray* da)
{
	PxUI fullPost = (PxUI) malloc(sizeof(struct postXusr_info));
	fullPost->answer = (GArray*) malloc(sizeof(struct GArray*));
	fullPost->usrID = (GArray*) malloc(sizeof(struct GArray*));
	fullPost->datas = (GArray*) malloc(sizeof(struct GArray*));

	fullPost->count = c + 1;
	fullPost->dateP = d;
	fullPost->answer = ans;
	fullPost->usrID = uID;
	fullPost->datas = da;

	return fullPost;
}

//Função que recebe parametros das parses e cria uma nova estrutura TI
TI
new_TI(long c)
{
	TI fullPost = (TI) malloc(sizeof(struct tag_Info));
	
	fullPost->id = c;

	return fullPost;
}

//------------------------------------------------


//Função que recebe uma TAD_community e devolve uma Gtree com PSTI
GTree*
get_posts(TAD_community com)
{
	return com->treePosts;
}

//Função que recebe uma TAD_community e devolve uma Gtree com USRP
GTree*
get_users(TAD_community com)
{
	return com->treeUsers;
}

//Função que recebe uma TAD_community e devolve uma GHash com UxPI
GHashTable*
get_hash_users(TAD_community com)
{
	return com->userXinfo;
}

//Função que recebe uma TAD_community e devolve uma GHash com PxUI
GHashTable*
get_hash_posts(TAD_community com)
{
	return com->infoXuser;
}

//Função que recebe uma TAD_community e devolve uma GHash com TI
GHashTable*
get_hash_tag(TAD_community com)
{
	return com->tagInfo;
}

//Função que recebe uma PSTI e devolve o ID do post
int get_post_id(PSTI post)
{
	return post->postID;
}

//Função que recebe uma PSTI e devolve o user do post
int get_post_user(PSTI post)
{
	return post->pUsrID;
}

//Função que recebe uma PSTI e devolve o tipo do post
int get_post_type(PSTI post)
{
	return post->pType;
}

//Função que recebe uma PSTI e devolve a pergunta mãe da resposta
int get_post_parent(PSTI post)
{
	return post->parentID;
}

//Função que recebe uma PSTI e devolve o score do post
int get_post_score(PSTI post)
{
	return post->score;
}

//Função que recebe uma PSTI e devolve o numero de comments do post
int get_post_comm(PSTI post)
{
	return post->comments;
}

//Função que recebe uma PSTI e devolve o titulo do post
char* get_post_title(PSTI post)
{
	return post->titulo;
}

//Função que recebe uma PSTI e devolve as tags do post
char* get_post_tags(PSTI post)
{
	return post->tags;
}

//Função que recebe uma PSTI e devolve o tempo concatenado (2016-05-21 => 20160521) do post
int get_post_ccTime(PSTI post)
{
	return post->dataNumber;
}

//Função que recebe uma USRP e devolve o ID do user
long get_user_id(USRP user)
{
	return user->usrID;
}

//Função que recebe uma USRP e devolve a reputação do user
int get_user_rep(USRP user)
{
	return user->reputation;
}

//Função que recebe uma USRP e devolve a biografia do user
char* get_user_bio(USRP user)
{
	return user->bio;
}

//Função que recebe uma USRP e devolve o nome do user
char* get_user_name(USRP user)
{
	return user->usrName;
}

//Função que recebe uma UxPI e devolve o numero total de posts do user
int get_post_total(UxPI user)
{
	return user->post_total;
}

//Função que recebe uma UxPI e devolve o GArray com os id's dos posts que o user publicou
GArray* get_postsID(UxPI user)
{
	return	user->postsID;
}

//Função que recebe uma UxPI e devolve o GArray com as datas dos posts que o user publicou
GArray* get_dat(UxPI user)
{
	return user->datas;
}

//Função que recebe uma UxPI e devolve o GArray com os id's das perguntas em que o user participou
GArray* get_quest(UxPI user)
{
	return user->questID;
}

//Função que recebe uma UxPI e devolve o GArray com as tags que o user usou
GArray* get_tags(UxPI user)
{
	return user->tags;
}

//Função que recebe uma PxUI e devolve o contador de elementos dos arrays
int get_counter(PxUI user)
{
	return user->count;
}

//Função que recebe uma PxUI e devolve a data de publicação do post
int get_date(PxUI user)
{
	return user->dateP;
}

//Função que recebe uma PxUI e devolve um GArray com o id das respostas a este post
GArray* get_answer(PxUI user)
{
	return user->answer;
}

//Função que recebe uma PxUI e devolve um GArray com o id dos users que participaram nele atraves de respostas
GArray* get_usrID(PxUI user)
{
	return user->usrID; 
}

//Função que recebe uma PxUI e devolve um GArray com a data das respostas a este post
GArray* get_datas(PxUI user)
{
	return user->datas;
}

//Função que recebe uma TI e devolve o id da tag
long get_id(TI user)
{
	return user->id;
}


















































