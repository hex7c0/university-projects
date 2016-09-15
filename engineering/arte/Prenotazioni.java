package arte;
import web.*;

public class Prenotazioni
{
    private Utente utente;
    private Opera opera;
    private Visite visita;
    private int giorno;
    private int mese;
    
    public Prenotazioni(Visite v, Opera o, Utente u,int giorno,int mese)
    {
        setVisita(v);
        setOpera(o);
        setUtente(u);
        setGiorno(giorno,mese);
    }
    
    public void setVisita(Visite v)
    {
        this.visita = v;
    }
    
    public int getGiorno()
    {
        return giorno;
    }
    
    public Visite getVisita()
    {
        return visita;
    }
    
    public int getMese()
    {
        return mese;
    }
    
    public void setGiorno(int giorno,int mese)
    {
        this.giorno = giorno;
        this.mese = mese;
    }

    public void setOpera(Opera o)
    {
        this.opera = o;
    }

    public void setUtente(Utente u)
    {
        this.utente = u;
    }
    
    public String printTicket()
    {
        String u = utente.getAnagr();
        String o = opera.getNome();
        String v = visita.getInfo();
        String out = "\nVisita : "+v+"\nGiorno: "+giorno+"/"+mese+"\nOpera : "+o+"\nNominativo : "+u;
        return out;
    }
}
