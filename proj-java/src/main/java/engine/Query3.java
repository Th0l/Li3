
/**
 * Write a description of class Query3 here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
package engine;

import common.Community;
import common.Pair;
import common.help_struct_1;
import common.help_struct_2;
import common.posts_str;
import common.postXusr;
import common.users_str;
import common.usrXpost;

import java.util.Set;
import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;

public class Query3
{
    /**
    * Dado um intervalo de tempo4 arbitrário, obtem o
    * numero total de posts
    * @param begin Data Inicial (concatenizada 2016-07-11 = 20160711)
    * @param end Data final (concatenizada 2016-07-11 = 20160711)
    * @return Pair<Long,Long> onde o 1º Elemento => Numero de Perguntas
    *                                2ª Elemento => Numero de Respostas
    */
    public Pair<Long,Long> query3(long begin,long end)
    {
        HashMap<Long,posts_str> posts = Community.infoPosts;

        long contR = 0;
        long contP = 0;

        Iterator it = posts.entrySet().iterator();

        while(it.hasNext())
        {
            Map.Entry pair = (Map.Entry)it.next();
            posts_str post = (posts_str) pair.getValue();
            long data = post.getData();

            if((data >= begin) && (data <= end))
            {
                long type = post.getType();

                if(type == 1)
                    contP++;
                else
                    contR++;
            }
        }

        Pair<Long,Long> ret = new Pair(contP,contR);
        return ret;
    }
}
