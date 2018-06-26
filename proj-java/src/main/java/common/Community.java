
/**
 * Classe com a Estrutura Geral.
 * Que vai guardar toda a informação necessaria sobre os dados lidos a partir
 * dos ficheiros .xml
 */
package common;

import engine.Parser;

import java.util.Set;
import java.util.Map;
import java.util.HashMap;

public class Community
{
    public static HashMap<Long,users_str> infoUsers;
    public static HashMap<Long,posts_str> infoPosts;
    public static HashMap<String,Long> tags;
    public static HashMap<Long,usrXpost> posts_of_user;
    public static HashMap<Long,postXusr> answers_of_question;

    /**
     * Construtor Vazio
     */
    public Community()
    {
        infoUsers = new HashMap();
        infoPosts = new HashMap();
        tags = new HashMap();
        posts_of_user = new HashMap();
        answers_of_question = new HashMap();
    }

    public void load(String path)
    {
        Parser ps = new Parser();

        String path1 = path.concat("Users.xml");
        String path2 = path.concat("Posts.xml");
        String path3 = path.concat("Tags.xml");

        System.out.println("\nComeçou o parse");
        this.infoUsers = ps.userParser(path1);
        this.infoPosts = ps.postParser(path2);
        this.tags = ps.tagParser(path3);
        this.posts_of_user = ps.xtraUserParse(infoPosts);
        this.answers_of_question = ps.xtraPostParse(infoPosts);
        System.out.println("Acabou o parse");
    }
}
