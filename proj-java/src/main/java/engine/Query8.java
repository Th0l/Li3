
/**
 * Write a description of class Query8 here.
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

public class Query8
{
    /**
    * Estrtura usada para ordenar os id's pela sua data de publicação
    * antes de ser passado para  a List que é retornada
    */
    private class q8_support implements Comparable<q8_support>
    {
        private long id;
        private long data;

        public q8_support(long id,long data)
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

        public int compareTo(q8_support q8)
        {
            int compareData = (int) ((q8_support) q8).getData();

            return (compareData - (int) this.data);
        }
    }

    /**
    * Dado uma palavra, retorna os id's das N perguntas
    * mais recentes que a contêm no seu Titulo
    * @param word A palavra que se pretende usar como chave
    * @param N O numero de elementos que se pretende ter na lista
    * @return List<Long> Com os id's das N perguntas ordenados por ordem decrescente da data de publicação
    */
    public List<Long> query8(String word,int N)
    {
        String delet = "\\p{Punct}|\\p{Blank}";
        HashMap<Long,posts_str> infoPosts = Community.infoPosts;
        ArrayList<q8_support> ret = new ArrayList();
        List<Long> ret2 = new ArrayList();

        Iterator it = infoPosts.entrySet().iterator();

        while(it.hasNext())
        {
            Map.Entry pair = (Map.Entry)it.next();
            posts_str post = (posts_str) pair.getValue();
            long type = post.getType();

            if(type == 1)
            {
                String title = post.getTitulo();
                int marker = 0;
                String[] splitResult = title.split(delet);
                for(String s : splitResult)
                {
                    if(s.compareTo(word) == 0)
                        marker = 1;
                }

                if(marker == 1)
                {
                    long id = post.getID();
                    long data = post.getData();
                    q8_support insert = new q8_support(id,data);
                    ret.add(insert);
                    Collections.sort(ret);

                    long elements = ret.size();

                    if(elements > N)
                    {
                        ret.remove(N);
                    }
                }
            }
        }

        ret.trimToSize();

        Iterator<q8_support> ite = ret.iterator();
        while(ite.hasNext())
        {
            q8_support q8 = (q8_support) ite.next();
            ret2.add(q8.getId());
        }
        return ret2;
    }
}
