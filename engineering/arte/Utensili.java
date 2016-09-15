package arte;

public class Utensili extends Oggetti
{ 
    public Utensili()
    {
        nomeArea=super.getNomeArea();
    }

    public Utensili(String nome)
    {
        super(nome);
        nomeArea=super.getNomeArea();
    }
}