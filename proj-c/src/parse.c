#include "parse.h"

/**
 *Função usada pelas parsers para inserir a informação na Gtree de maneira a que seja ordenada pelo ID
*/
gint comparaID (gconstpointer id1, gconstpointer id2)
{
	return (id1 - id2);
}
/**
 * Função que vai dar parse aos ficheiros .xml com informação importante para a estrutura USRP//usr_posts
 */
GTree* 
parse_users(char* dump_path)
{
	GTree* arvore;

	xmlChar *xmlInfo;
	
	char *temp;

	char *file = "Users.xml";

	char *file_path = malloc(strlen(dump_path) + strlen(file) + 1);

	strcpy(file_path,dump_path);

	strcat(file_path,file);

	int id,rep;
	char* biografia;char* nome;

	arvore = g_tree_new(comparaID);

	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(file_path);

	if(doc == NULL){
		fprintf(stderr,"It went wrong bud. \n");
		return NULL;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL){
		fprintf(stderr,"young one, stop giving empty stuff \n");
		xmlFreeDoc(doc);
		return NULL;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "users")) {
		fprintf(stderr,"document of the wrong type\n");
		xmlFreeDoc(doc);
		return NULL;
	}
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

		if ((xmlStrcmp(cur->name, (const xmlChar *) "row"))){

			if(cur->next != NULL){

				cur = cur->next;

				xmlInfo = xmlGetProp(cur, (xmlChar*)"Id");
				temp = (char *) xmlInfo;
		    	id = atoi(temp);

				xmlInfo = xmlGetProp(cur, (xmlChar*)"Reputation");
				temp = (char *) xmlInfo;
		    	rep = atoi(temp);
		    	
		    	if((xmlInfo = xmlGetProp(cur, (xmlChar*)"AboutMe")) != NULL)
		    	{
		    		temp = (char *) xmlInfo;
		    		biografia = (char *) mystrdup(temp);
		    	}
		    	
		    	else{biografia = "Sem Informação";}
		    

		    	if((xmlInfo = xmlGetProp(cur, (xmlChar*)"DisplayName")) != NULL)
		    	{
		    		temp = (char *) xmlInfo;	    	
		    		nome = (char *) mystrdup(temp);
		    	}

		    	else{nome = "Sem Informação";}

		    	USRP fullUser = new_user(id,rep,biografia,nome);

		    	g_tree_insert (arvore, GINT_TO_POINTER(id) , fullUser);

			}
			

		}

	cur = cur->next;
	}

	xmlCleanupParser();
	xmlMemoryDump();

	xmlFreeDoc(doc);
	free(xmlInfo);
	free(file_path);

	return arvore ;
}

/**
 * Função que vai dar parse aos ficheiros .xml com informação importante para a estrutura PSTI//post_Information
 */

GTree*
parse_posts(char* dump_path)
{
	char *temp;
	char *file1 = "Posts.xml";
	char *file2 = "Votes.xml";
	char *file_path1 = malloc(strlen(dump_path) + strlen(file1) + 1);
	char *file_path2 = malloc(strlen(dump_path) + strlen(file2) + 1);


	strcpy(file_path1,dump_path);
	strcpy(file_path2,dump_path);
	strcat(file_path1,file1);
	strcat(file_path2,file2);

	int id,uid,type,parent,score,comm,data;
	char* titu;char* tags;
	Date timeOF;

	GTree* arvore;
	
	xmlChar *xmlInfo;
	
	xmlDocPtr doc1;
	
	xmlNodePtr cur;

	arvore = g_tree_new(comparaID);
	doc1 = xmlParseFile(file_path1);

	if(doc1 == NULL){
		fprintf(stderr,"It went wrong bud. \n");
		return NULL;
	}

	cur = xmlDocGetRootElement(doc1);

	if (cur == NULL){
		fprintf(stderr,"young one, stop giving empty stuff \n");
		xmlFreeDoc(doc1);
		return NULL;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "posts")) {
		fprintf(stderr,"document of the wrong type\n");
		xmlFreeDoc(doc1);
		return NULL;
	}
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

		if ((xmlStrcmp(cur->name, (const xmlChar *) "row"))){

			if(cur->next != NULL){

				cur = cur->next;

				xmlInfo = xmlGetProp(cur, (xmlChar*)"Id");
				temp = (char *) xmlInfo;
		    	id = atoi(temp);
		    	
				if((xmlInfo = xmlGetProp(cur, (xmlChar*)"OwnerUserId")) != NULL)
				{
					temp = (char *) xmlInfo;
		    		uid = atoi(temp);
		    	}

		    	else{uid = -2;}

				xmlInfo = xmlGetProp(cur, (xmlChar*)"Score");
				temp = (char *) xmlInfo;
				score = atoi(temp);

				xmlInfo = xmlGetProp(cur, (xmlChar*)"CommentCount");
				temp = (char *) xmlInfo;
				comm = atoi(temp);

				xmlInfo = xmlGetProp(cur, (xmlChar*)"CreationDate");
				temp = (char *) xmlInfo;

				timeOF = (Date) get_time(temp);

				data = ((get_year(timeOF)*10000)+(get_month(timeOF)*100)+(get_day(timeOF)));

				xmlInfo = xmlGetProp(cur, (xmlChar*)"PostTypeId");
				temp = (char *) xmlInfo;
				type = atoi(temp);
				
				if(type == 1)
				{
		    		if((xmlInfo = xmlGetProp(cur, (xmlChar*)"Title")) != NULL)
		    		{
		    			temp = (char *) xmlInfo;
		    			titu = (char *) mystrdup(temp);
		    		}
		    	
		    		else{titu = "Sem Informação";}

		    		if((xmlInfo = xmlGetProp(cur, (xmlChar*)"Tags")) != NULL)
		    		{
		    			temp = (char *) xmlInfo;
		    			tags = (char *) mystrdup(temp);
		    		}
		    	
		    		else{tags = "Sem Informação";}

		    		parent = -2;
			
				}

				else
				{
					if((xmlInfo = xmlGetProp(cur, (xmlChar*)"ParentId")) != NULL)
					{
						temp = (char *) xmlInfo;
						parent = atoi(temp);
					}

					else{parent = -2;}

					titu = "Este post é uma resposta, logo não possui um titulo";
					tags = "Este post é uma resposta, logo não possui tags";
				}

				PSTI fullPost = new_post(id,uid,type,parent,score,comm,titu,tags,data);

				g_tree_insert (arvore, GINT_TO_POINTER(id) , fullPost);
			}
		}
	cur = cur->next;
	}


	xmlCleanupParser();
	xmlMemoryDump();

	xmlFreeDoc(doc1);	
	free(xmlInfo);	
	free(file_path1);
	free(file_path2);	
	return arvore ;
}

/**
 * Função que vai dar parse aos ficheiros .xml com informação importante para a estrutura UxPI//usrXpost_info
 */
GHashTable*
parse_UInfo(char* dump_path)
{

	GHashTable* hash;
	GArray* array;
	GArray* arraY;
	GArray* arrAy;
	GArray* aRRay;
	
	xmlChar *xmlInfo;

	char *file = "Posts.xml";

	char *file_path = malloc(strlen(dump_path) + strlen(file) + 1);

	strcpy(file_path,dump_path);

	strcat(file_path,file);

	char *temp;

	char *tags;

	int contador, dat, ptid;

	long id, pId, id2;

	Date timeOF;

	hash = g_hash_table_new_full(g_direct_hash, g_direct_equal,NULL,NULL);

	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(file_path);

	if(doc == NULL){
		fprintf(stderr,"It went wrong bud. \n");
		return NULL;
	}

	cur = xmlDocGetRootElement(doc);//primeira raiz p/ex:<tags>

	if (cur == NULL){
		fprintf(stderr,"young one, stop giving empty stuff \n");
		xmlFreeDoc(doc);
		return NULL;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "posts")) {
		fprintf(stderr,"document of the wrong type, root node != tags \n");
		xmlFreeDoc(doc);
		return NULL;
	}
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

		if ((xmlStrcmp(cur->name, (const xmlChar *) "row"))){

			if(cur->next != NULL){

				cur = cur->next;

				xmlInfo = xmlGetProp(cur, (xmlChar*)"CreationDate");
				temp = (char *) xmlInfo;
				timeOF = (Date) get_time(temp);
				dat = ((get_year(timeOF)*10000)+(get_month(timeOF)*100)+(get_day(timeOF)));

				xmlInfo = xmlGetProp(cur, (xmlChar*)"Id");
				temp = (char *) xmlInfo;
				pId = atoi(temp);

				xmlInfo = xmlGetProp(cur, (xmlChar*)"PostTypeId");
				temp = (char *) xmlInfo;
				ptid = atoi(temp);

				
				if(ptid == 1){
						xmlInfo = xmlGetProp(cur, (xmlChar*) "Tags");
						if(xmlInfo!=NULL)
						{
							tags = (char *) xmlInfo;	
						}
						else
						{
							tags = "n/e";
						}

						xmlInfo = xmlGetProp(cur, (xmlChar*)"OwnerUserId");

						if(xmlInfo!=NULL){
								temp = (char *) xmlInfo;
				    			id = atoi(temp);
				    			gpointer xx=g_hash_table_lookup(hash,GINT_TO_POINTER(id));

				    			if(xx!=NULL){
									UxPI ww = (UxPI) xx;
									contador = get_post_total(ww);
									array = get_postsID(ww);
									arraY = get_dat(ww);
									arrAy = get_quest(ww);
									aRRay = get_tags(ww);
									g_array_append_val(array, pId);
									g_array_append_val(arraY, dat);
									g_array_append_val(arrAy, pId);
									g_array_append_val(aRRay, tags);
									}
								else{
									contador = 0;
									array = g_array_new(FALSE, FALSE, sizeof(int));
									arraY = g_array_new(FALSE, FALSE, sizeof(int));
									arrAy = g_array_new(FALSE, FALSE, sizeof(int));
									aRRay = g_array_new(FALSE, FALSE, sizeof(char *));
									g_array_append_val(array, pId);
									g_array_append_val(arraY, dat);
									g_array_append_val(arrAy, pId);
									g_array_append_val(aRRay, tags);									
									}
				    			}

				    	else{	
				    			id=-2;
				    			gpointer xx=g_hash_table_lookup(hash,GINT_TO_POINTER(id));

				    			if(xx!=NULL){
									UxPI ww = (UxPI) xx;
									contador = get_post_total(ww);
									array = get_postsID(ww);
									arraY = get_dat(ww);
									arrAy = get_quest(ww);
									aRRay = get_tags(ww);
									g_array_append_val(array, pId);
									g_array_append_val(arraY, dat);
									g_array_append_val(arrAy, pId);
									g_array_append_val(aRRay, tags);
									}
								else{
									contador = 0;
									array = g_array_new(FALSE, FALSE, sizeof(int));
									arraY = g_array_new(FALSE, FALSE, sizeof(int));
									arrAy = g_array_new(FALSE, FALSE, sizeof(int));
									aRRay = g_array_new(FALSE, FALSE, sizeof(char *));
									g_array_append_val(array, pId);
									g_array_append_val(arraY, dat);
									g_array_append_val(arrAy, pId);
									g_array_append_val(aRRay, tags);
									}
				    	}
				    }

				if(ptid==2){

						tags= "n/e";

						xmlInfo = xmlGetProp(cur, (xmlChar*)"ParentId");
						temp = (char *) xmlInfo;
						id2 = atoi(temp);

						xmlInfo = xmlGetProp(cur, (xmlChar*)"OwnerUserId");

						if(xmlInfo!=NULL){
								temp = (char *) xmlInfo;
				    			id = atoi(temp);
				    			gpointer xx=g_hash_table_lookup(hash,GINT_TO_POINTER(id));

				    			if(xx!=NULL){
									UxPI ww = (UxPI) xx;
									contador = get_post_total(ww);
									array = get_postsID(ww);
									arraY = get_dat(ww);
									arrAy = get_quest(ww);
									aRRay = get_tags(ww);
									g_array_append_val(array, pId);
									g_array_append_val(arraY, dat);
									g_array_append_val(arrAy, id2);
									g_array_append_val(aRRay, tags);
									}
								else{
									contador = 0;
									array = g_array_new(FALSE, FALSE, sizeof(int));
									arraY = g_array_new(FALSE, FALSE, sizeof(int));
									arrAy = g_array_new(FALSE, FALSE, sizeof(int));
									aRRay = g_array_new(FALSE, FALSE, sizeof(char *));
									g_array_append_val(array, pId);
									g_array_append_val(arraY, dat);
									g_array_append_val(arrAy, id2);
									g_array_append_val(aRRay, tags);
									}
			    			}

				    	else{	
				    			id=-2;
				    			gpointer xx=g_hash_table_lookup(hash,GINT_TO_POINTER(id));

				    			if(xx!=NULL){
									UxPI ww = (UxPI) xx;
									contador = get_post_total(ww);
									array = get_postsID(ww);
									arraY = get_dat(ww);
									arrAy = get_quest(ww);
									aRRay = get_tags(ww);
									g_array_append_val(array, pId);
									g_array_append_val(arraY, dat);
									g_array_append_val(arrAy, id2);
									g_array_append_val(aRRay, tags);
									}
								else{
									contador = 0;
									array = g_array_new(FALSE, FALSE, sizeof(int));
									arraY = g_array_new(FALSE, FALSE, sizeof(int));
									arrAy = g_array_new(FALSE, FALSE, sizeof(int));
									aRRay = g_array_new(FALSE, FALSE, sizeof(char *));
									g_array_append_val(array, pId);
									g_array_append_val(arraY, dat);
									g_array_append_val(arrAy, id2);
									g_array_append_val(aRRay, tags);
									}
				    		}	
				    }
				    
		    	UxPI f_UxPI = new_UxPI(contador, array, arraY, arrAy, aRRay);
		    	g_hash_table_insert(hash,GINT_TO_POINTER(id),f_UxPI);
			}
			

		}

	cur = cur->next;
	}

	xmlCleanupParser();
	xmlMemoryDump();

	xmlFreeDoc(doc);
	free(xmlInfo);
	free(file_path);

	return hash;

}

/**
 * Função que vai dar parse aos ficheiros .xml com informação importante para a estrutura PxUI//postXusr_info
 */
GHashTable*
parse_PInfo(char* dump_path)
{
	GHashTable* hash;
	
	GArray* array;
	GArray* arraY;
	GArray* arrAy;
	
	xmlChar *xmlInfo;

	char *file = "Posts.xml";

	char *file_path = malloc(strlen(dump_path) + strlen(file) + 1);

	strcpy(file_path,dump_path);

	strcat(file_path,file);
	
	char *temp;

	int contador, typeId, OwnId, data, datP = 0, dat;

	long id, iD;

	Date timeOF;

	hash = g_hash_table_new_full(g_direct_hash, g_direct_equal,NULL,NULL);

	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(file_path);

	if(doc == NULL){
		fprintf(stderr,"It went wrong bud. \n");
		return NULL;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL){
		fprintf(stderr,"young one, stop giving empty stuff \n");
		xmlFreeDoc(doc);
		return NULL;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "posts")) {
		fprintf(stderr,"document of the wrong type, root node != tags \n");
		xmlFreeDoc(doc);
		return NULL;
	}
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

		if ((xmlStrcmp(cur->name, (const xmlChar *) "row"))){

			if(cur->next != NULL){

				cur = cur->next;

				xmlInfo = xmlGetProp(cur, (xmlChar*)"CreationDate");
				temp = (char *) xmlInfo;
				timeOF = (Date) get_time(temp);
				dat = ((get_year(timeOF)*10000)+(get_month(timeOF)*100)+(get_day(timeOF)));

				xmlInfo = xmlGetProp(cur, (xmlChar*)("Id"));
				temp = (char *) xmlInfo;
				id = atoi(temp);
				gpointer xx = g_hash_table_lookup(hash,GINT_TO_POINTER(id));

				if(xx!=NULL){
						PxUI ww = (PxUI) xx;
						contador = get_counter(ww);
						array = get_answer(ww);
						arraY = get_usrID(ww);
						arrAy = get_datas(ww);
						datP = get_date(ww);
					}
				else{
						contador = 0;
						array = g_array_new(FALSE,FALSE,sizeof(int));
						arraY = g_array_new(FALSE,FALSE,sizeof(int));
						arrAy = g_array_new(FALSE,FALSE,sizeof(int));
					}
					
				xmlInfo = xmlGetProp(cur, (xmlChar*)("PostTypeId"));
				temp = (char *) xmlInfo;
				typeId = atoi(temp);

				if(typeId==2){//se é resposta
						xmlInfo = xmlGetProp(cur, (xmlChar*)("ParentId"));
						temp = (char *) xmlInfo;
						iD = atoi(temp);
						gpointer zz = g_hash_table_lookup(hash,GINT_TO_POINTER(iD));

						if(zz!=NULL){
							PxUI yy = (PxUI) zz;
							contador = get_counter(yy);
							array = get_answer(yy);
							arraY = get_usrID(yy);
							arrAy = get_datas(yy);
							datP = get_date(yy);
					}
						else{
							contador = 0;
							array = g_array_new(FALSE,FALSE,sizeof(int));
							arraY = g_array_new(FALSE,FALSE,sizeof(int));
							arrAy = g_array_new(FALSE,FALSE,sizeof(int));
					}
					
					xmlInfo = xmlGetProp(cur, (xmlChar*)("OwnerUserId"));
					if(xmlInfo!=NULL){
						temp = (char *) xmlInfo;
						OwnId=atoi(temp);
					}
					else{
						OwnId=-2;
					}

					data = dat;
					
					g_array_append_val(arrAy, data);
					g_array_append_val(array, id);
					g_array_append_val(arraY, OwnId);

					PxUI fPxUI = new_PxUI(contador, datP, array, arraY, arrAy);
					g_hash_table_insert(hash, GINT_TO_POINTER(iD), fPxUI);
				}
				else{
					datP = dat;
				}
				if(typeId==1){
				PxUI f_PxUI = new_PxUI(contador, datP, array, arraY, arrAy);
		    	g_hash_table_insert(hash, GINT_TO_POINTER(id), f_PxUI);}
			}
		}

	cur = cur->next;
	}

	xmlCleanupParser();
	xmlMemoryDump();
	
	xmlFreeDoc(doc);
	free(xmlInfo);
	free(file_path);

	return hash;

}

GHashTable*
parse_Tag(char* dump_path)
{
	GHashTable* hash;
	
	xmlChar *xmlInfo;

	char *file = "Tags.xml";

	char *file_path = malloc(strlen(dump_path) + strlen(file) + 1);

	strcpy(file_path,dump_path);

	strcat(file_path,file);
	
	char *temp;
	char *name;
	long id; 

	hash = g_hash_table_new_full(g_str_hash, g_str_equal,NULL,NULL);

	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(file_path);

	if(doc == NULL){
		fprintf(stderr,"It went wrong bud. \n");
		return NULL;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL){
		fprintf(stderr,"young one, stop giving empty stuff \n");
		xmlFreeDoc(doc);
		return NULL;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *) "tags")) {
		fprintf(stderr,"document of the wrong type, root node != tags \n");
		xmlFreeDoc(doc);
		return NULL;
	}
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {

		if ((xmlStrcmp(cur->name, (const xmlChar *) "row"))){

			if(cur->next != NULL){

				cur = cur->next;

				xmlInfo = xmlGetProp(cur, (xmlChar*)"TagName");
				temp = (char *) xmlInfo;
				name = temp;

				xmlInfo = xmlGetProp(cur, (xmlChar*)"Id");
				temp = (char *) xmlInfo;
				id = (long) atoi(temp);

				TI f_TI = new_TI(id);
				g_hash_table_insert(hash, name, f_TI);
			}
		}

	cur = cur->next;
	}

	xmlCleanupParser();
	xmlMemoryDump();
	
	xmlFreeDoc(doc);
	free(xmlInfo);
	free(file_path);

	return hash;

}
