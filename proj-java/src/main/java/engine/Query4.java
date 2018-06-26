
/**
 * Write a description of class Query4 here.
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

public class Query4
{
    /**
    * Estrtura usada para ordenar os id's pela sua data de publicação
    * antes de ser passado para  a List que é retornada
    */
    private class q4_support implements Comparable<q4_support>
    {
        private long id;
        private long data;

        public q4_support(long id,long data)
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

        public int compareTo(q4_support q4)
        {
            int compareData = (int) ((q4_support) q4).getData();

            return (compareData - (int) this.data);
        }
    }

    /**
    * Dado um intervalo de tempo arbitrário, retornar todas
    * as perguntas contendo uma determinada tag
    * @param word Tag que se quer procurar
    * @param begin Data Inicial (concatenizada 2016-07-11 = 20160711)
    * @param end Data final (concatenizada 2016-07-11 = 20160711)
    * @return List<Long> Com os id's das perguntas ordenadas do mais recente para o mais antigo
    */
    public List<Long> query4(String word,long begin,long end)
    {
        String tag = "<".concat(word).concat(">");
        HashMap<Long,posts_str> posts = Community.infoPosts;
        ArrayList<q4_support> ret = new ArrayList();
        List<Long> ret2 = new ArrayList();

        Iterator it = posts.entrySet().iterator();

        while(it.hasNext())
        {
            Map.Entry pair = (Map.Entry)it.next();
            posts_str post = (posts_str) pair.getValue();
            long type = post.getType();

            if(type == 1)
            {
                String pTag = post.getTags();

                if(pTag.contains(tag))
                {
                    long data = post.getData();

                    if(data >= begin && data <= end)
                    {
                        long id = post.getID();
                        q4_support insert = new q4_support(id,data);
                        ret.add(insert);
                        Collections.sort(ret);
                    }
                }
            }
        }

        Iterator<q4_support> ite = ret.iterator();
        while(ite.hasNext())
        {
            q4_support q4 = (q4_support) ite.next();
            ret2.add(q4.getId());
        }
        return ret2;
    }
}
