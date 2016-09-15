package arte;

public class Visite {

    private int oraH,oraM;
    private boolean speciale = false;
    private String guida = "";
    
    public Visite(int orarioH,int orarioM)
    {
        setOrario(orarioH,orarioM);        
    }
    
    public void setGuida(String nome)
    {
        guida = nome;
    }
    
    public void setOrario(int oraH,int oraM)
    {
        this.oraH=oraH;
        this.oraM=oraM;
    }
    
    public void setSpeciale()
    {
        speciale = true;
    }
    
    public int getOra()
    {
        return oraH;
    }
    
    public String getInfo()
    {
        String out="";
        out = "\nOrario : "+oraH+":"+oraM+"\nGuida : "+guida;
        return out;
    }
    
    public String getOrario()
    {
        String out="";
        out = "Orario : "+oraH+":"+oraM;
        return out;
    }
    
    public boolean isSpeciale()
    {
        return (speciale == true);
    } 
}    