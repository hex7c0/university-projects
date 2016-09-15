package arte;
import web.*;

public class EventiSpec
{
    private Visite visita;
    private Museo museo;
    
    public EventiSpec(Visite v, Museo m)
    {
        setVisita(v);
        setMuseo(m);
    }
    
    public void setVisita(Visite v)
    {
        if (v.isSpeciale())
            this.visita = v;
        else
            System.out.println("Non è una visita possibile!!!\n");
    }
 
    public Visite getVisita()
    {
        return visita;
    }
    
    public void setMuseo(Museo m)
    {
        this.museo = m;
        m.addEvento(this);
    }

    public Museo getMuseo()
    {
        return museo;
    }
    
    public String toString()
    {
        StringBuffer result = new StringBuffer();
        String m = museo.getNome();
        String v = visita.getInfo();
        String out = "\nEvento Speciale : "+v+"\nMuseo : "+m+"\n";
        result.append(out);               
        return result.toString();
    }
}