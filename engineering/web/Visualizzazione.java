package web;

import java.util.*;

public abstract class Visualizzazione
{
    protected String dispositivo;
    protected String risoluzione="";
    protected ArrayList tagParse = new ArrayList();
    protected Pagina P;
    private int isFrameSet = 0;
    
    public void display()
    {
        System.out.println("Visualizzazione su "+dispositivo);
    }
   
    public String getDispositivo()
    {
        return dispositivo;
    }
   
    public void setRisoluzione(String r)
    {
        this.risoluzione = r;       
    }
    
    public String getRisoluzione()
    {
        return this.risoluzione;       
    }
    
    public void addTagParse(Componenti c)
    {
        tagParse.add(c);    
    }
    
    public ArrayList getTagParse()
    {
        return tagParse;    
    }
    
    public String getDispVis()
    {    
        String out ="\t\t______________________________________________________________________________\n\n";   
        out +="\t\t\tVisualizzazione su "+dispositivo + " con risoluzione "+this.risoluzione+"\n";
        out +="\t\t______________________________________________________________________________\n\n";
        return out;
    }
    
    public String browse(Pagina Pag)
    {
        this.P = Pag;        
        return parse();
    }
    
    protected String parse()
    {
        String head_contenuto ="", body_contenuto ="";
        // scomposizione in componenti
        ArrayList head = P.getHeader();
        Bodypage  body = new Bodypage();
        body = P.getBody();
        ArrayList body_tag  = body.getTag();
        //confronto degli header gestibili
        ArrayList newTag  = new ArrayList();        
        int trovato = 0;  
        String t_Tag = "";
        
        for (int i=0; i< head.size(); i++)
        {
            Componenti h = (Componenti) head.get(i);
            trovato=0;
            for (int j=0; j< tagParse.size() && trovato==0; j++)
            {                
                Componenti t = (Componenti) tagParse.get(j);
                if (t.getStrTag() == h.getStrTag()) trovato=1; 
            }
            if (trovato==1)
                head_contenuto += h.getComponent() + "\n";
              else
                head_contenuto += h.getComponentAlt()+"\n ";
        }
        
        trovato=0;
        t_Tag = "";
        //ridefinizione dei tag in funzione del dispositivo
        for (int i=0; i< body_tag.size(); i++)
        {
            trovato=0;
            Componenti b = (Componenti) body_tag.get(i);            
            for (int j=0; j< tagParse.size() && trovato==0; j++)
            {
                Componenti t = (Componenti) tagParse.get(j);
                String str_tag = t.getStrTag();
                if ( str_tag.equals("FRAME"))
                    isFrameSet=1;
                if (t.getStrTag() == b.getStrTag()) trovato=1;              
            }            
            if (trovato==1)
                body_contenuto += b.getComponent() +"\n ";
            else
                body_contenuto += b.getComponentAlt()+"\n ";
        }
        // creazione di una nuova pagina    
        
        return makePage(head_contenuto, body_contenuto);
    }
    
    protected String makePage(String head, String body)
    {
        String contenuto = "<html>";
        contenuto += "<head>\n<title>"+P.getTitolo()+"</title>\n";
        contenuto += "\n"+ head +"\n";
        contenuto += "</head>";
        if(isFrameSet==0)
            contenuto += "\n<body>\n"+ body +"\n</body>\n";
        else
            contenuto += "\n"+ body +"\n";
        //Contenuti Generici
        contenuto += "</html>";
        return contenuto;
    }
}