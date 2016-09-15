package web;

import java.util.*;
import arte.*;

public class Utente extends Users{
// lista delle aree di competenza di un utente
    private ArrayList lsAree; 
    private int esperto;

    public Utente()
    {
        super();
        esperto=0;
        lsAree = new ArrayList();
    }   

    public void addAree(AreeCompetenza a)
    {
        if(lsAree!=null)
            lsAree.add(a);
    }

    public void setEsperto(AreeCompetenza a)
    {
        esperto = 1;    
        addAree(a);
    }
    
    public ArrayList getAree()
    {
       return lsAree;
    }
    
    public int isExpert()
    {
        return esperto;
    }
}
