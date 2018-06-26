
/**
 * Esta estrutura permite guardar informação especifica sobre um post sem se
 * estar a percorrer o HashMap dos posts inteiro sempre que se quer fazer uma
 * das queries
 */
package common;

import java.util.ArrayList;

public class postXusr
{
    private long dataPergunta; //data en que esta pergunta foi publicada
    private long numRespostas; //numero total de respostas que a pergunta possui
    private ArrayList<help_struct_2> respID; //todos os id's das respostas que é possuido pela pergunta

    /**
     * Constructor for objects of class postXusr
     */
    public postXusr()
    {
        this.dataPergunta = 0;
        this.numRespostas = 0;
        this.respID = new ArrayList();
    }

    public postXusr(long data,long num,ArrayList<help_struct_2> resp)
    {
        this.dataPergunta = data;
        this.numRespostas = num;
        this.respID = resp;
    }

    public postXusr(postXusr psu)
    {
        this.dataPergunta = psu.getDataP();
        this.numRespostas = psu.getNumR();
        this.respID = psu.getRespostas();
    }

    public long getDataP()
    {
        return this.dataPergunta;
    }

    public long getNumR()
    {
        return this.numRespostas;
    }

    public ArrayList<help_struct_2> getRespostas()
    {
        return this.respID;
    }

    public void setDataP(long data)
    {
        this.dataPergunta = data;
    }

    public void setNumR(long num)
    {
        this.numRespostas = num;
    }

    public void setRespostas(ArrayList<help_struct_2> hs2)
    {
        this.respID = hs2;
    }

    public postXusr clone()
    {
        return new postXusr(this);
    }

    public boolean equals(Object o)
    {
        if(o==this) return true;
        if(o==null || o.getClass() != this.getClass() ) return false;
        postXusr c = (postXusr) o;
        boolean ret = c.dataPergunta == this.dataPergunta && c.numRespostas == this.numRespostas && this.respID.equals(c.respID);
        return ret;
    }

    public String toString() {

        StringBuilder sb = new StringBuilder();

        sb.append("Data de Publicaçao: ");
        sb.append(this.dataPergunta + "\n");
        sb.append("Numero de Respostas: ");
        sb.append(this.numRespostas + "\n");
        sb.append("Respostas dadas a pergunta:");
        sb.append("\n" + this.respID.toString());

        return sb.toString();
    }
}
