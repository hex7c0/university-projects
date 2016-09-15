package arte;

import java.util.*;

public class Sala {
    private ArrayList lsOpere; // lista delle Opera della Sala
    private String nome;  

    public Sala(String name)
    {
        this.nome=name;
        lsOpere= new ArrayList();
    }   

    public ArrayList getOpere()
    {
        return lsOpere;
    }
    
    public void addOpera(Opera o)
    {
        lsOpere.add(o);
    }
    
    public String getInfo()
    {
        return  this.nome;
    }
}
