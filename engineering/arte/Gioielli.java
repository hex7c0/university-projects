package arte;

public class Gioielli extends Oggetti
{ 
    public Gioielli()
    {
        nomeArea=super.getNomeArea();
    }

    public Gioielli(String nome)
    {
        super(nome);
        nomeArea=super.getNomeArea();
    }
}