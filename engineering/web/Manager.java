package web;

import java.util.*;
import arte.*;

public class Manager extends Users{
    
    public Manager(String n, String c)
    {
        setAnagr(n, c);
        String id = c.toLowerCase() +".adm";
        String pass = n.toLowerCase();
        setUserId( id, pass);
        admin=0;
    }   
    
    public void UpToExpert(Utente u,AreeCompetenza a)
    {
        u.setEsperto(a);
    }
        
    public void setAdmin()
    {
        admin=1;
    }

    public void setSede(Sede s)
    {
        this.sede=s;
    }

    public void addMuseo(Museo m)
    {        
        Ministero mi = new Ministero();
        mi = (Ministero) this.sede;
        mi.addMuseo(m);
    }
    
    public void addOpera(Opera o)
    {
        Museo m = new Museo();
        m = (Museo) this.sede;
        m.addOpera(o);    
    }
}