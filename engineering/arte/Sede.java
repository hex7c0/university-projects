package arte;
import web.*;

public abstract class Sede
{
    protected String nome;
  	protected String citta;
    protected Manager admin;

    public Sede()
    {}
    
    public String getNome()
    {
        return nome;
    }

}
