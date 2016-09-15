package arte;

import java.util.*;
import java.util.Iterator;
import web.*;


public class Museo extends Sede {
    
    private String direttore;
    private ArrayList lsSale; //lista Sale
    private ArrayList lsOpere;//lista Opere 
    private ArrayList lsVisite;//lista Visite disponibili
    private ArrayList lsPrenotazioni;//lista Visite disponibili
    private ArrayList lsEventi;//lista Eventi Speciali
    private ArrayList results;// lista delle opere cercate
    
    private Manager manager;
       
    public Museo()
    {
    }   

    public Museo(String name)
    {
        this.nome=name;
        lsOpere= new ArrayList();
        lsSale= new ArrayList();
        lsVisite= new ArrayList();
        lsEventi= new ArrayList();        
        lsPrenotazioni= new ArrayList();
    }   
    
    public String getNome()
    {
        return nome;
    }
    
    public void setManager(Manager m)
    {
        manager=m;
        m.setSede(this);
    }
    
    public ArrayList getOpere()
    {
        return lsOpere;
    }
        
    public ArrayList findOpera(String nome,String autore)
    {
        results=lsOpere;
 
        if(!(nome.equals("*")))
            results = findOperaNome(nome);
        if(!(autore.equals("*")))
            results = findOperaAutore(autore);
        return results;
    }
    
    public ArrayList findOperaNome(String nome)
    {
        ArrayList temp = new ArrayList();
        
        for(int i=0;i<results.size();i++)
        {
            Opera a = (Opera) results.get(i);
            if(a.getNome().equals(nome))
                temp.add(a);
        }
        return temp;
    }    
    
    public ArrayList findOperaAutore(String autore)
    {
        ArrayList temp = new ArrayList();
        
        for(int i=0;i<results.size();i++)
        {
            Opera a = (Opera) results.get(i);
            if(a.getAutore().equals(autore))
                temp.add(a);
        }
        return temp;
    }    
       
    public void addOpera(Opera o)
    {
        lsOpere.add(o);
    }
    
    public ArrayList getSale()
    {
        return lsSale;
    }
    
    public void addSala(Sala s)
    {
        lsSale.add(s);
    }
    
    public ArrayList getVisite()
    {
        return lsVisite;
    }
    
    public void addVisita(Visite v)
    {
        lsVisite.add(v);
    }
    
    public ArrayList getPrenotazioni()
    {
        return lsPrenotazioni;
    }
    
    public void addPrenotazione(Prenotazioni p)
    {
        lsPrenotazioni.add(p);
    }
    
    public boolean checkDisponibilita(int giorno,int mese,Visite v)
    {
        for(int i=0;i<lsPrenotazioni.size();i++)
        {
                 Prenotazioni pr = (Prenotazioni) lsPrenotazioni.get(i);
                 if((giorno == pr.getGiorno()) && (mese == pr.getMese()) && (v.getOra() == pr.getVisita().getOra()))
                    return false;
        }
        return true;
    }
    
    public void addEvento(EventiSpec e)
    {
        lsEventi.add(e);
    }

    public ArrayList getEventi()
    {
        return lsEventi;
    }
}
