package web;

import java.util.*;

public class Bodypage extends Pagine
{
    protected ArrayList comp;//sezione BODY della pagina WEB
    ArrayList links = new ArrayList();
    int setframe = 0;
    
    public Bodypage() 
    {
         if (comp==null)  
            comp = new ArrayList();
    }
    
    public Bodypage(String bodycontent)
    {
        if (comp==null) 
            comp = new ArrayList();
        Componenti html=new HTML(bodycontent);
        comp.add(html);
    }
 
    public void BodyFrame(Frame bodyframe)
    {
        this.setframe  = 1;
        if (comp==null) 
            comp = new ArrayList();
        comp.add(bodyframe);
    }  
    
    public void addLink (String url, String testo)
    {
        String html_link = "<a href="+url+" target=\"_parent\">"+testo+"</a><br/>";
        links.add(html_link);
    }
    
    public void addLink (String url, Immagine i)
    {
        String html_link = "<a href="+url+" target=\"_parent\">"+i.getComponent()+"</a><br/>";
        links.add(html_link);
    }
    
    public String getListLink()
    {
       String out ="";
       for (int i=0; i< links.size(); i++)
        {
            String  f = (String) links.get(i);
            out += f + "\n";
        }  
        return out;
    }

    public void addComponet(Componenti c)
    {
        comp.add(c);
    }
    
    public String getComponent()
    {
        if (this.setframe==1)
        {
            Componenti  f = (Componenti) comp.get(0);
            contenuto = f.getComponent() + "\n";
            return contenuto;
        }   
        else
        {
            contenuto = "<body>";
            //Contenuti Generici
            for (int i=0; i< comp.size(); i++)
            {
                Componenti  f = (Componenti) comp.get(i);
                contenuto += f.getComponent() + "\n";
            }
            String links= getListLink();
            if (links!="")
                contenuto += "Elenco delle pagine collegate direttamente : " + links +"\n\n";
            contenuto += "</body>";
            return contenuto;
        }
    }

    public ArrayList getTag()
    {
        return comp;    
    }
}