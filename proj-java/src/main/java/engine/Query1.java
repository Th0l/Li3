
/**
 * Write a description of class Query1 here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
package engine;

import common.Pair;
import common.Community;
import common.help_struct_1;
import common.help_struct_2;
import common.posts_str;
import common.postXusr;
import common.users_str;
import common.usrXpost;

import java.util.HashMap;

public class Query1
{
    /**
    * Dado o identificador de um post, o metodo retorna
    * o título do post e o nome de utilizador do autor
    * @param id Long que representa o identificador do post
    * @return Pair<String,String>, 1º elemento -> Título
    *                              2ª elemento -> Nome de utilizador
    */
    public Pair<String,String> query1(long id)
    {
        HashMap<Long,users_str> users = Community.infoUsers;
        HashMap<Long,posts_str> posts = Community.infoPosts;

        if(posts.containsKey(id)) //Se o id existe ou não
        {
            posts_str post = posts.get(id);
            long type = post.getType();

            if(type == 1) //Se for uma pergunta
            {
                String titulo = post.getTitulo();
                long uid = post.getUsrID();

                if(users.containsKey(uid)) //Verifica se user existe
                {
                    users_str user = users.get(uid);
                    String nome = user.getName();
                    Pair<String,String> ret = new Pair(titulo,nome);

                    return ret;
                }
                else //User que publicou nao existe
                {
                    System.out.println("O user nao existe");
                    return null;
                }
            }
            else //Se for uma resposta
            {
                long parent = post.getParent();

                if(posts.containsKey(parent))
                {
                    post = posts.get(parent);
                    String titulo = post.getTitulo();
                    long uid = post.getUsrID();

                    if(users.containsKey(uid))  //Verifica se user existe
                    {
                        users_str user = users.get(uid);
                        String nome = user.getName();
                        Pair<String,String> ret = new Pair(titulo,nome);

                        return ret;
                    }
                    else //User que publicou nao existe
                    {
                        System.out.println("O user nao existe");
                        return null;
                    }
                }
                else //Pergunta originativa da resposta nao existe
                {
                    System.out.println("A pergunta mae da resposta com o ID fornecido nao existe");
                    return null;
                }
            }
        }
        else //Se o id nao existir na base de dados
        {
            System.out.println("Nao existe um post com esse Id\n");
            return null;
        }
    }
}
