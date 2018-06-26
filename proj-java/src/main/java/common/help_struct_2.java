
/**
 * Write a description of class help_struct_2 here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
package common;

public class help_struct_2 implements Comparable<help_struct_2>
{
    private long idResposta;
    private long idUser;
    private long data;

    /**
     * Constructor for objects of class help_struct_2
     */
    public help_struct_2()
    {
        this.idResposta = 0;
        this.idUser = 0;
        this.data = 0;
    }

    public help_struct_2(long idR,long idU,long data)
    {
        this.idResposta = idR;
        this.idUser = idU;
        this.data = data;
    }

    public help_struct_2(help_struct_2 hs2)
    {
        this.idResposta = hs2.getIDR();
        this.idUser = hs2.getIDU();
        this.data = hs2.getData();
    }

    public void setIDR(long id)
    {
        this.idResposta = id;
    }

    public void setIDU(long id)
    {
        this.idUser = id;
    }

    public void setData(long data)
    {
        this.data = data;
    }

    public long getIDR()
    {
        return this.idResposta;
    }

    public long getIDU()
    {
        return this.idUser;
    }

    public long getData()
    {
        return this.data;
    }

    public help_struct_2 clone()
    {
        return new help_struct_2(this);
    }

    public boolean equals(Object o)
    {
        if(o==this) return true;
        if(o==null || o.getClass() != this.getClass() ) return false;
        help_struct_2 c = (help_struct_2) o;
        boolean ret = c.idResposta == this.idResposta && this.data == c.data && c.idUser == this.idUser;
        return ret;
    }

    public String toString() {

        StringBuilder sb = new StringBuilder();

        sb.append("ID da Resposta: ");
        sb.append(this.idResposta);
        sb.append(" || ID do User: ");
        sb.append(this.idUser);
        sb.append(" || Data de publicaçao: ");
        sb.append(this.data);

        return sb.toString();
    }

    public int compareTo(help_struct_2 hs2)
    {
        int compareData = (int) ((help_struct_2) hs2).getData();

        return (compareData - (int) this.data);
    }
}
