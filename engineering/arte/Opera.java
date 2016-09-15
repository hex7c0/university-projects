package arte;

import java.util.*;
import web.*;

public abstract class Opera implements AreeCompetenza
{
   private String nome;
   private int anno;
   private String autore;
   private String nazione;
   protected String nomeArea;
   private String foto;
   private Sala sala;
   private Museo museo;
   
   Informazioni info;
   
   public Opera()
   {
   }
   
   public Opera(String nome)
   {
       setNome(nome);
   }
   
   public void setInfo(Informazioni info)
   {
       this.info=info;
   }
   
   public String getSala()
   {
       return sala.getInfo();
   }
   
   public void setSala(Sala s)
   {
       sala=s;
       sala.addOpera(this);
   }
   
   public String getMuseo()
   {
       return museo.getNome();
   }
   
   public void setMuseo(Museo m)
   {
       museo=m;
       museo.addOpera(this);
   }
   
   public String getInfo(Utente u)
   {
       if(u == null)
           return info.getDescrizione(false);
       if(u.isExpert()==1)
        {
            ArrayList aree=u.getAree();
            for(int i=0;i<aree.size();i++)
            {
                AreeCompetenza a = (AreeCompetenza) aree.get(i);
                if(a.getNomeArea() == getNomeArea())
                    return info.getDescrizione(true);
            }
        } 
        return info.getDescrizione(false);
   }
   
   public void setNome(String nome)
   {
       this.nome=nome;
   }
   
   public void setFoto(String foto)
   {
       this.foto=foto;
   }
   
   public void setAnno(int anno)
   {
       this.anno=anno;
   }
   
   public void setNazione(String nazione)
   {
       this.nazione=nazione;
   }
   
   public void setNomeArea(String nomeArea)
   {
       this.nomeArea=nomeArea;
   }
   
   public String getNome()
   {
       return nome;
   }
   
   public int getAnno()
   {
       return anno;
   }
   
   public String getFoto()
   {
       return foto;
   }
    
   public String getNazione()
   {
       return nazione;
   }
   
   public String getNomeArea()
   {
        return nomeArea;
   }
   
    public void setArea(Utente u)
    {
        u.addAree(this); 
    }
    
    public void setAutore(String autore)
   {
        this.autore=autore;
   }
    
    public String getAutore()
    {
        return autore;
    }
}