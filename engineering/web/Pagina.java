package web;

import java.util.*;

public class Pagina extends Pagine
{
    protected Bodypage html = new Bodypage();
    ArrayList script;  //sezione HEAD della pagina WEB
    protected String frameset = "";
    
    public Pagina()
    {
        this.SitePage  = new ArrayList();
        this.tagParse = new ArrayList();
        this.script = new ArrayList();
    }
    
    public Pagina(String Nome, String Descrizione) {
        this.titolo = Descrizione; //"Homepage";
        this.nome_pagina = Nome;//"index.html";
        this.SitePage  = new ArrayList();
        this.tagParse = new ArrayList();
        this.script = new ArrayList();
    }
    
    public void addScript(Componenti s)
    {
        script.add(s);
    }
    
    public void addBody(Bodypage h)
    {
        this.html=h;
    }   
    
    public void addFrameSet(String frame)
    {
        this.frameset=frame;
    }   
    
    public String getFrame()
    {
        return frameset;
    }
   
    public String getComponent1()
    {
        contenuto = "<html>";
        contenuto += "<head><title>"+titolo+"</title>\n";
        //Stili
        for (int i=0; i< script.size(); i++)
        {
            Componenti  s = (Componenti) script.get(i);
            contenuto += s.getComponent() + "\n";
        }
        contenuto += "</head>\n";
        contenuto += html.getComponent();
        //Contenuti Generici
        contenuto += "</html>";
        return contenuto;
    }
    
    public ArrayList getHeader()
    {
        return script;
    }
    
    public Bodypage getBody()
    {
        return html;
    }
}