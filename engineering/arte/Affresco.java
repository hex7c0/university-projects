package arte;

public class Affresco extends Pittura
{
    public Affresco()
    {
        nomeArea=super.getNomeArea();
    }

    public Affresco(String nome)
    {
        super(nome);
        nomeArea=super.getNomeArea();
    }
}