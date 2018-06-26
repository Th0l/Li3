
/**
 * Write a description of class Query10 here.
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

import java.util.HashMap;
import java.util.ArrayList;
import java.util.Iterator;

public class Query10
{
    /**
    * Dado o identificador de uma pergunta, devolve a resposta
    * que tem o melhor score
    * @param id identificador da perguntas
    * @return Long, identificador da resposta com o melhor score
    */
    public long query10(long id)
    {
        HashMap<Long,users_str> users = Community.infoUsers;
        HashMap<Long,posts_str> posts = Community.infoPosts;
        HashMap<Long,postXusr> answers = Community.answers_of_question;

        double max = 0,comp = 0;
        long maxID = -1,compID = -1;

        if(answers.containsKey(id))
        {
            postXusr post = answers.get(id);

            if(post.getNumR() == 0)
                System.out.println("-1\n");

            ArrayList<help_struct_2> resp = post.getRespostas();
            Iterator<help_struct_2> it = resp.iterator();
            while(it.hasNext())
            {
                help_struct_2 hs2 = (help_struct_2) it.next();
                long repID = hs2.getIDR();
                long userID = hs2.getIDU();

                if(posts.containsKey(repID))
                {
                    if(users.containsKey(userID))
                    {
                        posts_str rep = posts.get(repID);
                        users_str user = users.get(userID);

                        long score = rep.getScore();
                        long comm = rep.getComm();
                        long reputaçao = user.getRep();

                        comp = (double) ((score * 0.65)+(comm * 0.1)+(reputaçao * 0.25));
                        compID = repID;

                        if(comp > max)
                        {
                            max = comp;
                            maxID = compID;
                        }
                    }
                }
            }
            return maxID;
        }
        else
            return maxID;
    }
}
