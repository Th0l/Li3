
/**
 * Write a description of class Query7 here.
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

public class Query7
{
    /**
    * Estrutura usada para ordenar os id's por ordem decrescente do num de respostas
    * antes de ser passado para a List que é retornada
    */
    private class q7_support implements Comparable<q7_support>
    {
        private long id;
        private long numRespostas;

        public q7_support(long id,long num)
        {
            this.id = id;
            this.numRespostas = num;
        }

        public long getId()
        {
            return this.id;
        }

        public long getNumR()
        {
            return this.numRespostas;
        }

        public int compareTo(q7_support q7)
        {
            int compareData = (int) ((q7_support) q7).getNumR();

            return (compareData - (int) this.numRespostas);
        }
    }

    /**
    * Dado um intervalo de tempo arbitrário, retorna os
    * id's das N perguntas com mais respostas
    * @param N O numero de elementos que se pretende ter na lista
    * @param begin Data Inicial (concatenizada 2016-07-11 = 20160711)
    * @param end Data final (concatenizada 2016-07-11 = 20160711)
    * @return List<Long> Com os id's das N perguntas ordenados por ordem decrescente do numero de respostas
    */
    public List<Long> query7(int N,long begin,long end)
    {
        HashMap<Long,postXusr> ansq = Community.answers_of_question;
        ArrayList<q7_support> ret = new ArrayList();
        List<Long> ret2 = new ArrayList();

        Iterator it = ansq.entrySet().iterator();

        while(it.hasNext())
        {
            Map.Entry pair = (Map.Entry)it.next();
            postXusr post = (postXusr) pair.getValue();
            long data = post.getDataP();
            ArrayList<help_struct_2> resp = post.getRespostas();

            if(data >= begin && data <= end)
            {
                long counter = 0;
                Iterator<help_struct_2> ite = resp.iterator();
                while(ite.hasNext())
                {
                    help_struct_2 hs2 = (help_struct_2) ite.next();
                    data = hs2.getData();

                    if(data >= begin && data <= end)
                    {
                        counter++;
                    }
                }

                long id = (long) pair.getKey();
                q7_support q7 = new q7_support(id,counter);
                ret.add(q7);
                Collections.sort(ret);

                long elements = ret.size();

                if(elements > N)
                {
                    ret.remove(N);
                }
            }
        }

        ret.trimToSize();

        Iterator<q7_support> its = ret.iterator();
        while(its.hasNext())
        {
            q7_support q7 = (q7_support) its.next();
            ret2.add(q7.getId());
        }
        return ret2;
    }
}
