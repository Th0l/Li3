
/**
 * Write a description of class Query5 here.
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
import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;

public class Query5
{
    /**
    * Dado o identificador de um utilizador, o metodo retorna
    * a sua Biografia e os seus ultimos 10 posts
    * @param id Long que representa o identificador do post
    * @return Pair<String,List<Long>>, 1º elemento -> Biografia
    *                                  2ª elemento -> Uma List com os id's dos posts ordenada do mais recente para
    *                                                 o mais antigo
    */
    public Pair<String, List<Long>> query5(long id)
    {
        HashMap<Long,users_str> users = Community.infoUsers;
        HashMap<Long,usrXpost> userP = Community.posts_of_user;
        List<Long> ret = new ArrayList();
        Pair<String,List<Long>> ret2;
        String bioR;
        int fSize = 0,counter = 0;

        if(users.containsKey(id) && userP.containsKey(id))
        {
            users_str user = users.get(id);
            bioR = user.getBio();

            usrXpost posts = userP.get(id);

            long size = 10;
            long postTot = posts.getPostTot();

            if(postTot < size)
            {
                fSize = (int) postTot;
            }
            else
            {
                fSize = (int) 10;
            }

            ArrayList<help_struct_1> userPost = posts.getPostID();

            Iterator<help_struct_1> it = userPost.iterator();

            while(counter < fSize && it.hasNext())
            {
                help_struct_1 hs1 = (help_struct_1) it.next();
                ret.add(counter,hs1.getID());
                counter++;
            }

            ret2 = new Pair(bioR,ret);
            return ret2;
        }
        else
        {
            System.out.println("Nao existe nenhum user com esse id");
            return null;
        }
    }
}
