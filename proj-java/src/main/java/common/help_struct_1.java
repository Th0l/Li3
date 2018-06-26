
/**
 * Write a description of class help_struct_1 here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
package common;

public class help_struct_1 implements Comparable<help_struct_1>
{
    private long id;
    private long data;

    /**
     * Constructor for objects of class help_struct_1
     */
    public help_struct_1()
    {
        this.id = 0;
        this.data = 0;
    }

    public help_struct_1(long id,long data)
    {
        this.id = id;
        this.data = data;
    }

    public help_struct_1(help_struct_1 hs1)
    {
        this.id = hs1.getID();
        this.data = hs1.getData();
    }

    public void setID(long id)
    {
        this.id = id;
    }

    public void setData(long data)
    {
        this.data = data;
    }

    public long getID()
    {
        return this.id;
    }

    public long getData()
    {
        return this.data;
    }

    public help_struct_1 clone()
    {
        return new help_struct_1(this);
    }

    public boolean equals(Object o)
    {
        if(o==this) return true;
        if(o==null || o.getClass() != this.getClass() ) return false;
        help_struct_1 c = (help_struct_1) o;
        boolean ret = c.id == this.id && this.data == c.data;
        return ret;
    }

    public String toString() {

        StringBuilder sb = new StringBuilder();

        sb.append("ID do Post: ");
        sb.append(this.id);
        sb.append(" || Data de publicaçao: ");
        sb.append(this.data);

        return sb.toString();
    }

    public int compareTo(help_struct_1 hs1)
    {
        int compareData = (int) ((help_struct_1) hs1).getData();

        return (compareData - (int) this.data);
    }
}
