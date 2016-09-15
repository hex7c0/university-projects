package web;

import java.util.*;

public abstract class Pagine
{
    protected String risoluzione="";
    ArrayList tagParse = new ArrayList();  //tag Parserizzabili - componenti
    
    ArrayList SitePage;
    Visualizzazione dispositivo;
    
    String contenuto = " ";
    protected String titolo = "Pagina Senza Titolo";
    protected String description = "Pagina sconosciuta";    
    protected String nome_pagina = "nome della pagina";
    
    public String getName() {
        String out = this.nome_pagina;
        return out;
    }
    public String getTitolo()
    {
        return titolo;    
    }
    
    public void addPagina(Pagine P)
    {
        SitePage.add(P);
    }
    
    public String getPagine()
    {
        String str="";   
        for(int i=0;i<SitePage.size();i++)
        {
            Pagine s = (Pagine) SitePage.get(i);
            str += "\t\n\t - "+i+" : - "+s.getInfo();
        }
        return str;
    }
    
    public String getInfo() {
        String out = getTitolo();
        String pagine;
        if ((pagine=getPagine())!="")
            out += "\n\tPagine collegate di "+getName()+" :"+ pagine;
        return out;
    }
 
    public void setRisoluzione(String r)
    {
        this.risoluzione = r;       
    }
    
    public void parseTag(ArrayList t)
    {
        this.tagParse=t;
    }
    
    public String browse()
    {   
        String out;
        if (this.risoluzione!="")
            out="Visializzazione in risoluzione "+this.risoluzione + " (Ottimizzata)";
        else out="";
        return out;
    }   
}