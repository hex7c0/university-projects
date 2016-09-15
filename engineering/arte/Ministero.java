package arte;

import java.util.*;
import web.*;

public class Ministero extends Sede
{
    private ArrayList lsMusei; // lista dei musei del ministero
    private ArrayList lsManager;
    private ArrayList lsUtenti;
    private ArrayList lsAree;

    public Ministero()
    {
    }
    
    public Ministero(String name)
    {
        this.nome=name;
        lsMusei = new ArrayList();
        lsManager = new ArrayList();
        lsUtenti = new ArrayList();
        lsAree = new ArrayList();
        setlsAree();
    }   
    
    public void setlsAree()
    {
        lsAree.add(new Pittura());
        lsAree.add(new Oggetti());
        lsAree.add(new Arazzi());
        lsAree.add(new Scultura());
    }
    
    public void setAdmin(Manager a)
    {
        this.admin=a;
        a.setSede(this);
        lsManager.add(a);
        a.setAdmin();
        
    }

    public void addManager(Manager m, Museo museo)
    {
        lsManager.add(m);
        museo.setManager(m);
    }
    
    public void addMuseo(Museo m)
    {
        lsMusei.add(m);
    }
    
    public ArrayList getMusei()
    {
        return lsMusei;
    }
    
    public ArrayList getlsAree()
    {
        return lsAree;
    }
    
    public ArrayList getlsUtenti()
    {
        return lsUtenti;
    }

    public ArrayList getUser()
    {
        return lsUtenti;
    }
    
    public Users getRegistered(String uname,String pass)
    {   
        int trovato = 0;
        Utente man=null;
        for(int i=0;i<lsUtenti.size() && (trovato!=1);i++)
        {
            man = (Utente) lsUtenti.get(i);
            trovato = man.isUser(uname,pass);         
        }
        if (trovato==1)
            return man;
        return null;
    }
    
    public Manager getManager(String uname,String pass)
    {     
        int trovato = 0;
        Manager man=null;
        for(int i=0;(i<lsManager.size()) && ((trovato!=1));i++)
        {
            man = (Manager) lsManager.get(i);
            trovato = man.isUser(uname,pass);
            
        }
        if (trovato==1)
            return man;
        return null;
    }
    
    public ArrayList findOpera(String museo,String nome,String autore)
    {
        ArrayList search=new ArrayList();
        ArrayList temp;
        
        if(museo.equals("*"))
        {
            for(int i=0;i<lsMusei.size();i++)
            {
                Museo m = (Museo) lsMusei.get(i);
                temp = m.findOpera(nome,autore);
                for(int j=0;j<temp.size();j++)
                    search.add((Opera)temp.get(j));
            }
            return search;
        }     
        else
        {
            for(int i=0;i<lsMusei.size();i++)
            {
                Museo m = (Museo) lsMusei.get(i);
                if(m.getNome().equals(museo))
                    return m.findOpera(nome,autore);
            }
        }
        return null;
    }
    
    public void addRegistered(Utente u) {
        System.out.println(u.getUserID());
        lsUtenti.add(u);
    }
    
    public void removeRegistered(Utente u) {
        int i = lsUtenti.indexOf(u);
        if (i >= 0) {
            lsUtenti.remove(i);
        }
    }
    
    public String toString() 
    {
        StringBuffer result = new StringBuffer();
        result.append("\n\t\t"+ nome +" - Repubblica Italiana");
        result.append("\n");
        return result.toString();
    }
   
    public ArrayList getEventi()
    {
        ArrayList eventi=new ArrayList();
        ArrayList temp;
        
        for(int i=0;i<lsMusei.size();i++)
        {
            Museo m = (Museo) lsMusei.get(i);
            temp = m.getEventi();
            for(int j=0;j<temp.size();j++)
                eventi.add((EventiSpec)temp.get(j));
        }
    return eventi;
    }
}
