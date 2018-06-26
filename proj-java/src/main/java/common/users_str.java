
/**
* Esta estrutura vai ser a estrutura principal para guardar toda a informação
* necessaria sobre um utilizador na altura em que se da parse ao ficheiro
* "users.xml"
*/
 package common;

public class users_str
{
   private long usrID; //ID do user
   private long reputation; // Reputaçao desse user
   private String bio; // Biografia do User
   private String usrName; // User Name

    /**
     * Construtor Vazio de users_str
     */
    public users_str()
    {
        this.usrID = -2;
        this.reputation = -2;
        this.bio = "n/e";
        this.usrName = "n/e";
    }

    public users_str(long id,long reputation,String bio,String usrName)
    {
        this.usrID = id;
        this.reputation = reputation;
        this.bio = bio;
        this.usrName = usrName;
    }

    public users_str(users_str xpto)
    {
        this.usrID = xpto.getID();
        this.reputation = xpto.getRep();
        this.bio = xpto.getBio();
        this.usrName = xpto.getName();
    }

    public void setID(long id)
    {
        this.usrID = id;
    }

    public void setRep(long rep)
    {
        this.reputation = rep;
    }

    public void setBio(String bio)
    {
        this.bio = bio;
    }

    public void setName(String name)
    {
        this.usrName = name;
    }

    public long getID()
    {
        return this.usrID;
    }

    public long getRep()
    {
        return this.reputation;
    }

    public String getBio()
    {
        return this.bio;
    }

    public String getName()
    {
        return this.usrName;
    }

    public users_str clone()
    {
        return new users_str(this);
    }

    public boolean equals(Object o)
    {
        if(o==this) return true;
        if(o==null || o.getClass() != this.getClass() ) return false;
        users_str c = (users_str) o;
        boolean ret = c.usrID == this.usrID && this.usrName.equals(c.usrName) && this.bio.equals(c.bio) &&
                                 this.reputation == c.reputation;
        return ret;
    }

    public String toString() {

        StringBuilder sb = new StringBuilder();

        sb.append("ID do User: ");
        sb.append(this.usrID + "\n");
        sb.append("UserName: ");
        sb.append(this.usrName + "\n");
        sb.append("Reputation: ");
        sb.append(this.reputation + "\n");
        sb.append("Biography: ");
        sb.append(this.bio + "\n");

        return sb.toString();
    }



}
