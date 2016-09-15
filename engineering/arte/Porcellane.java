package arte;

public class Porcellane extends Oggetti
{ 
    public Porcellane()
    {
        nomeArea=super.getNomeArea();
    }

    public Porcellane(String nome)
    {
        super(nome);
        nomeArea=super.getNomeArea();
    }
}