
/**
 * Write a description of class Query2 here.
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

public class Query2
{
    /**
    * Estrtura usada para ordenar os id's por ordem decrescente do numero de posts
    * antes de ser passado para  a List que é retornada
    */
    private class q2_support implements Comparable<q2_support>
    {
        private long id;
        private long num;

        public q2_support(long id,long num)
        {
            this.id = id;
            this.num = num;
        }

        public long getId()
        {
            return this.id;
        }

        public long getNum()
        {
            return this.num;
        }

        public int compareTo(q2_support q2)
        {
            int compareData = (int) ((q2_support) q2).getNum();

            return (compareData - (int) this.num);
        }
    }

    /**
    * Metodo que devolve o top N utilizadores com
    * maior número de posts de sempre
    * @param N Integer que corresponde ao numero de elementos pretendidos
    * @return List<Long> que tem tamanho N e os identificadores dos users por ordem
    *         decrescente do numero de posts
    */
    public List<Long> query2(int N)
    {
        HashMap<Long,usrXpost> userP = Community.posts_of_user;
        ArrayList<q2_support> ret = new ArrayList();
        List<Long> ret2 = new ArrayList();

        Iterator it = userP.entrySet().iterator();

        while(it.hasNext())
        {
            Map.Entry pair = (Map.Entry)it.next();
            usrXpost usp = (usrXpost) pair.getValue();

            long posts = usp.getPostTot();
            long id = (long) pair.getKey();

            if(id >= 0)//Se o identificador for valido, pois existe um id=-1 nos ficheiros xml
            {
                q2_support insert = new q2_support(id,posts);
                ret.add(insert);
                Collections.sort(ret);

                long elements = ret.size();

                if(elements > N)
                {
                    ret.remove(N);
                }
            }
        }

        Iterator<q2_support> ite = ret.iterator();
        while(ite.hasNext())
        {
            q2_support q2 = (q2_support) ite.next();
            ret2.add(q2.getId());
        }
        return ret2;
    }
}
