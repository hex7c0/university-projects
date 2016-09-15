package arte;

public class Quadro extends Pittura
{
    public Quadro()
    {
        nomeArea=super.getNomeArea();
    }

    public Quadro(String nome)
    {
        super(nome);
        nomeArea=super.getNomeArea();
    }
}