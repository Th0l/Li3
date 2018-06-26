
/**
 * Esta estrutura permite guardar informação especifica sobre um user sem se
 * estar a percorrer o HashMap dos posts/users inteiro sempre que se quer fazer uma
 * das queries
 */
package common;

import java.util.ArrayList;

public class usrXpost
{
    private long post_total; //Numero Total de Posts feitos pelo user
    private ArrayList<help_struct_1> postID; //ID dos posts de qual o user fez
    private ArrayList<help_struct_1> questionID; //ID das perguntas das quais o user participou atraves de fazer uma resposta
    private ArrayList<String> tags; //Lista com todas as tags usadas pelo user nas suas Perguntas

    /**
     * Constructor for objects of class usrXpost
     */
    public usrXpost()
    {
        this.post_total = 0;
        this.postID = new ArrayList();
        this.questionID = new ArrayList();
        this.tags = new ArrayList();
    }

    public usrXpost(long posts,ArrayList<help_struct_1> postID,ArrayList<help_struct_1> questionID,ArrayList<String> tags)
    {
        this.post_total = posts;
        this.postID = postID;
        this.questionID = questionID;
        this.tags = tags;
    }

    public usrXpost(usrXpost info)
    {
        this.post_total = info.getPostTot();
        this.postID = info.getPostID();
        this.questionID = info.getQuestID();
        this.tags = info.getTags();
    }

    public long getPostTot()
    {
        return this.post_total;
    }

    public ArrayList<help_struct_1> getPostID()
    {
        return this.postID;
    }

    public ArrayList<help_struct_1> getQuestID()
    {
        return this.questionID;
    }

    public ArrayList<String> getTags()
    {
        return this.tags;
    }

    public void setPostTot(long post_total)
    {
        this.post_total = post_total;
    }

    public void setPostID(ArrayList<help_struct_1> postID)
    {
        this.postID = postID;
    }

    public void setQuestID(ArrayList<help_struct_1> questionID)
    {
        this.questionID = questionID;
    }

    public void setTags(ArrayList<String> tags)
    {
        this.tags = tags;
    }

    public usrXpost clone()
    {
        return new usrXpost(this);
    }

    public boolean equals(Object o)
    {
        if(o==this) return true;
        if(o==null || o.getClass() != this.getClass() ) return false;
        usrXpost c = (usrXpost) o;
        boolean ret = c.post_total == this.post_total && this.postID.equals(c.postID) && this.questionID.equals(c.questionID) &&
                                 this.tags.equals(c.tags);
        return ret;
    }

    public String toString() {

        StringBuilder sb = new StringBuilder();

        sb.append("Numero total de posts: ");
        sb.append(this.post_total + "\n");
        sb.append("Questoes e Perguntas feitas pelo User:");
        sb.append("\n" + this.postID.toString());
        sb.append("\nQuestoes feitas pelo user: ");
        sb.append(this.questionID.toString() + "\n");
        sb.append("Tags usadas pelo user: ");
        sb.append(this.tags.toString() + "\n");

        return sb.toString();
    }
}
