
/**
 * Write a description of class Query9 here.
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

public class Query9
{
    /**
    * Estrtura usada para ordenar os id's pela sua data de publicação
    * antes de ser passado para  a List que é retornada
    */
    private class q9_support implements Comparable<q9_support>
    {
        private long id;
        private long data;

        public q9_support(long id,long data)
        {
            this.id = id;
            this.data = data;
        }

        public long getId()
        {
            return this.id;
        }

        public long getData()
        {
            return this.data;
        }

        public int compareTo(q9_support q9)
        {
            int compareData = (int) ((q9_support) q9).getData();

            return (compareData - (int) this.data);
        }
    }

    /**
    * Dado dois identificadores de users, retorna os id's das N perguntas
    * mais recentes em que ambos os users participaram
    * @param id1 O primeiro identificador de user
    * @param id2 O segundo identificador de user
    * @param N O numero de elementos que se pretende ter na lista
    * @return List<Long> Com os id's das N perguntas ordenados por ordem decrescente da data de publicação
    */
    public List<Long> query9(long id1,long id2,int N)
    {
        HashMap<Long,usrXpost> pou = Community.posts_of_user;
        ArrayList<q9_support> ret = new ArrayList();
        List<Long> ret2 = new ArrayList();

        if(pou.containsKey(id1) && pou.containsKey(id2))
        {
            usrXpost user1 = pou.get(id1);
            usrXpost user2 = pou.get(id2);
            ArrayList<help_struct_1> userQ1 = user1.getQuestID();
            ArrayList<help_struct_1> userQ2 = user2.getQuestID();
            int marker;

            Iterator<help_struct_1> it = userQ1.iterator();
            while(it.hasNext())
            {
                help_struct_1 us1 = (help_struct_1) it.next();
                marker = 0;
                long qid1 = us1.getID();
                Iterator<help_struct_1> ite = userQ2.iterator();
                while(ite.hasNext() && marker == 0)
                {
                    help_struct_1 us2 = (help_struct_1) ite.next();
                    long qid2 = us2.getID();

                    if(qid1 == qid2)
                    {
                        q9_support insert = new q9_support(qid2,us2.getData());
                        ret.add(insert);
                        Collections.sort(ret);
                        marker = 1;
                        long elements = ret.size();
                        if(elements > N)
                        {
                            ret.remove(N);
                        }
                    }
                }
            }

            ret.trimToSize();

            Iterator<q9_support> its = ret.iterator();
            while(its.hasNext())
            {
                q9_support q9 = (q9_support) its.next();
                if(!ret2.contains(q9.getId()))
                  ret2.add(q9.getId());
            }
            return ret2;
        }
        else
        {
            System.out.println("Um dos users fornecidos nao existe");
            return null;
        }
    }
}
