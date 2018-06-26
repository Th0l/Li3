
/**
 * Write a description of class Query6 here.
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
import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;
import java.util.Collections;

public class Query6
{
    /**
    * Estrutura usada para ordenar os id's por ordem decrescente do score
    * antes de ser passado para  a List que é retornada
    */
    private class q6_support implements Comparable<q6_support>
    {
        private long id;
        private long score;

        public q6_support(long id,long score)
        {
            this.id = id;
            this.score = score;
        }

        public long getId()
        {
            return this.id;
        }

        public long getScore()
        {
            return this.score;
        }

        public int compareTo(q6_support q6)
        {
            int compareData = (int) ((q6_support) q6).getScore();

            return (compareData - (int) this.score);
        }
    }

    /**
    * Dado um intervalo de tempo arbitrário, retorna os
    * id's das N respostas com mais votos
    * @param N O numero de elementos que se pretende ter na lista
    * @param begin Data Inicial (concatenizada 2016-07-11 = 20160711)
    * @param end Data final (concatenizada 2016-07-11 = 20160711)
    * @return List<Long> Com os id's das N respostas ordenados por ordem decrescente do numero de votos
    */
    public List<Long> query6(int N,long begin,long end)
    {
        HashMap<Long,posts_str> infoPosts = Community.infoPosts;
        ArrayList<q6_support> ret = new ArrayList();
        List<Long> ret2 = new ArrayList();

        Iterator it = infoPosts.entrySet().iterator();

        while(it.hasNext())
        {
            Map.Entry pair = (Map.Entry)it.next();
            posts_str post = (posts_str) pair.getValue();
            long type = post.getType();
            long data = post.getData();

            if(type == 2 && data >= begin && data <= end)
            {
                long score = post.getScore();
                long id = post.getID();
                q6_support insert = new q6_support(id,score);
                ret.add(insert);
                Collections.sort(ret);

                long elements = ret.size();

                if(elements > N)
                {
                    ret.remove(N);
                }
            }
        }

        ret.trimToSize();

        Iterator<q6_support> ite = ret.iterator();
        while(ite.hasNext())
        {
            q6_support q6 = (q6_support) ite.next();
            ret2.add(q6.getId());
        }
        return ret2;
    }
}
