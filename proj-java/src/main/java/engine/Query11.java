
/**
 * Write a description of class Query11 here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
package engine;

import common.Community;
import common.help_struct_1;
import common.help_struct_2;
import common.posts_str;
import common.postXusr;
import common.users_str;
import common.usrXpost;

import java.util.Set;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Collections;

public class Query11
{
    /**
    * Estrtura usada para ordenar os id's das tags pelo seu numero de usos
    * antes de ser passado para  a List que é retornada
    */
    private class q11_support implements Comparable<q11_support>
    {
        private long id;
        private long counter;

        public q11_support(long id,long counter)
        {
            this.id = id;
            this.counter = counter;
        }

        public long getId()
        {
            return this.id;
        }

        public long getCounter()
        {
            return this.counter;
        }

        public int compareTo(q11_support q11)
        {
            int compareData = (int) ((q11_support) q11).getCounter();

            return (compareData - (int) this.counter);
        }
    }

    /**
    * Dado um intervalo de tempo arbitrário, retorna os
    * id's das N tags mais usadas pelos utilizadores com melhor reputação
    * @param N O numero de elementos que se pretende ter na lista
    * @param begin Data Inicial (concatenizada 2016-07-11 = 20160711)
    * @param end Data final (concatenizada 2016-07-11 = 20160711)
    * @return List<Long> Com os id's das N tags mais usadas ordenadas por ordem decrescente do numero de usos
    */
    public List<Long> query11(int N,long begin,long end)
    {
        HashMap<Long,users_str> infoUsers = Community.infoUsers;
        HashMap<Long,posts_str> infoPosts = Community.infoPosts;
        HashMap<Long,usrXpost> pou = Community.posts_of_user;
        HashMap<String,Long> tags = Community.tags;
        ArrayList<q11_support> topUsers = new ArrayList(); //Array que vai ter os ids dos Top N users
        HashMap<Long,Integer> tempTags = new HashMap(); //Map que vai ter os ids de todas as tags usadas pelos users
        ArrayList<q11_support> ret = new ArrayList(); //Array que vai ter os ids das Top N Tags
        List<Long> ret2 = new ArrayList();

        Iterator it = infoUsers.entrySet().iterator();

        while(it.hasNext()) //Ciclo While que vai determinar qual os users com melhor Reputaçao
        {
            Map.Entry pair = (Map.Entry)it.next();
            users_str user = (users_str) pair.getValue();

            q11_support insert = new q11_support(user.getID(),user.getRep());
            topUsers.add(insert);
            Collections.sort(topUsers);
            long elements = topUsers.size();
            if(elements > N) //Se o numero de elementos for maior que N, vai-se remover o ultimo, para nao se ter arrays desnecessariamente grandes
            {
                topUsers.remove(N);
            }
        }

        Iterator<q11_support> its = topUsers.iterator();
        while(its.hasNext()) //Ciclo while que vai percorrer o ArrayList gerado no while em cima de modo a obter os seus posts
        {
            q11_support q11 = (q11_support) its.next();
            if(pou.containsKey(q11.getId())) //Se o id existe na estrutura dos Users
            {
                usrXpost user = pou.get(q11.getId());
                ArrayList<help_struct_1> user_posts = user.getPostID();
                Iterator<help_struct_1> ite = user_posts.iterator();
                while(ite.hasNext()) //Caso o id exista, este ciclo while vai percorrer o ArrayList correspondente ao user que tem os Posts que ele fez
                {
                    help_struct_1 hs1 = (help_struct_1) ite.next();
                    if(infoPosts.containsKey(hs1.getID())) //Verificar se esta o post esta presente na informaçao do ficheiro Posts.xml
                    {
                        posts_str pst = infoPosts.get(hs1.getID());
                        long type = pst.getType();
                        long data = pst.getData();
                        if((type == 1) && (data >= begin) && (data <= end)) //Se for uma Pergunta e estiver dentro do intervalo de tempo pedido
                        {
                            String pTags = pst.getTags();
                            if(pTags.length() > 0) //Se nao for NULL
                            {
                                String[] splitTags = pTags.split("<|>");
                                for(String s : splitTags) //Vai percorrer todas as tags que a Pergunta tinha
                                {
                                    String tag = "<".concat(s).concat(">");
                                    if(tags.containsKey(tag)) //Verificar se esta tag esta presente na informaçao do ficheior Tags.xml
                                    {
                                        long tagId = tags.get(tag);
                                        if(tempTags.containsKey(tagId)) //Se o map com as tags usadas ja a contem ou nao
                                        {
                                            int counter = tempTags.get(tagId);
                                            counter++;
                                            tempTags.replace(tagId,counter);
                                        }
                                        else // Se nao a conter vai-se adicionar ao map
                                        {
                                            int ct = 0;
                                            tempTags.put(tagId,ct);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        it = tempTags.entrySet().iterator();

        while(it.hasNext()) //Ciclo While que vai determinar quais as N Tags mais usadas
        {
            Map.Entry pair = (Map.Entry)it.next();
            int counter = (int) pair.getValue();
            long id = (long) pair.getKey();
            q11_support insert2 = new q11_support(id,counter);
            ret.add(insert2);
            Collections.sort(ret);
            long elements = ret.size();
            if(elements > N) //Se o numero de elementos for maior que N, vai-se remover o ultimo, para nao se ter arrays desnecessariamente grandes
            {
                ret.remove(N);
            }
        }

        ret.trimToSize();

        Iterator<q11_support> ite = ret.iterator();
        while(ite.hasNext())
        {
            q11_support q11 = (q11_support) ite.next();
            ret2.add(q11.getId());
        }
        return ret2;
    }
}
