
/**
* Esta estrutura vai ser a estrutura principal para guardar toda a informação
* necessaria sobre um post na altura em que se da parse ao ficheiro
* "posts.xml"
*/
package common;

public class posts_str
{
   private long postID; //ID do Post
   private long pUsrID; // ID do user que fez o post
   private long pType; //Tipo de Post *1 = Pergunta || *2 = Resposta
   private long parentID; // Caso seja uma resposta, vai conter o ID da pergunta a qual esta a responder
   private long score; // Score do post
   private long comments; // Numero total de comentarios do post
   private String titulo; // Caso seja uma Pergunta, vai conter o seu Titulo
   private String tags; // Caso seja uma Pergunta, vai conter as tags associadas a ela
   private long dataNumber; // Data de publicaçao concatenada, i.e., 2010-10-30 -> 20101030

    /**
     * Construtor Vazio de users_str
     */
    public posts_str()
    {
        this.postID = -2;
        this.pUsrID = -2;
        this.pType = -2;
        this.parentID = -2;
        this.score = -2;
        this.comments = -2;
        this.dataNumber = -2;
        this.titulo = "n/e";
        this.tags = "n/e";
    }

    public posts_str(long id,long usrId,long type,long parent,long sc,long comm,long dataN,String titulo,String tags)
    {
        this.postID = id;
        this.pUsrID = usrId;
        this.pType = type;
        this.parentID = parent;
        this.score = sc;
        this.comments = comm;
        this.dataNumber = dataN;
        this.titulo = titulo;
        this.tags = tags;
    }

    public posts_str(posts_str xpto)
    {
        this.postID = xpto.getID();
        this.pUsrID = xpto.getUsrID();
        this.pType = xpto.getType();
        this.parentID = xpto.getParent();
        this.score = xpto.getScore();
        this.comments = xpto.getComm();
        this.dataNumber = xpto.getData();
        this.titulo = xpto.getTitulo();
        this.tags = xpto.getTags();
    }

    public void setID(long id)
    {
        this.postID = id;
    }

    public void setUsrID(long id)
    {
        this.pUsrID = id;
    }

    public void setType(long tp)
    {
        this.pType = tp;
    }

    public void setParent(long prID)
    {
        this.parentID = prID;
    }

    public void setScore(long sc)
    {
        this.score = sc;
    }

    public void setComm(long comm)
    {
        this.comments = comm;
    }

    public void setData(long dt)
    {
        this.dataNumber = dt;
    }

    public void setTitulo(String tit)
    {
        this.titulo = tit;
    }

    public void setTags(String tg)
    {
        this.tags = tg;
    }

    public long getID()
    {
        return this.postID;
    }

    public long getUsrID()
    {
        return this.pUsrID;
    }

    public long getType()
    {
        return this.pType;
    }

    public long getParent()
    {
        return this.parentID;
    }

    public long getScore()
    {
        return this.score;
    }

    public long getComm()
    {
        return this.comments;
    }

    public long getData()
    {
        return this.dataNumber;
    }

    public String getTitulo()
    {
        return this.titulo;
    }

    public String getTags()
    {
        return this.tags;
    }

    public posts_str clone()
    {
        return new posts_str(this);
    }

    public boolean equals(Object o)
    {
        if(o==this) return true;
        if(o==null || o.getClass() != this.getClass() ) return false;
        posts_str c = (posts_str) o;
        boolean ret = c.postID == this.postID && this.titulo.equals(c.titulo) && this.tags.equals(c.tags) &&
                                  this.pUsrID == c.pUsrID && this.pType == c.pType && this.parentID == c.parentID &&
                                  this.score == c.score && this.comments == c.comments && this.dataNumber == c.dataNumber;
        return ret;
    }

    public String toString() {

        StringBuilder sb = new StringBuilder();

        sb.append("ID do Post: ");
        sb.append(this.postID + "\n");
        sb.append("Tipo de Post: ");
        sb.append(this.pType + "\n");
        sb.append("ID do Publicador: ");
        sb.append(this.pUsrID + "\n");
        if(this.pType == 1)
        {
            sb.append("Titulo: ");
            sb.append(this.titulo + "\n");
            sb.append("Tags: ");
            sb.append(this.tags + "\n");
        }
        else
        {
            sb.append("ID da pergunta correspondente: ");
            sb.append(this.parentID + "\n");
        }
        sb.append("Score: ");
        sb.append(this.score + "\n");
        sb.append("Numero total de comentarios: ");
        sb.append(this.comments + "\n");
        sb.append("Data de Publicaçao: ");
        sb.append(this.dataNumber + "\n");

        return sb.toString();
    }
}
