package arte;

public class InformazioniComuni implements Informazioni
{
    private String luogoRitrovo;
    private int annoRitrovo;
    private Informazioni i;
    
    public InformazioniComuni(String luogoRitrovo,int annoRitrovo)
    {
        setLuogoRitrovo(luogoRitrovo);
        setAnnoRitrovo(annoRitrovo);
    }
    
    public void setInfoExpert(Informazioni info)
    {
        i=info;
    }
    
    public void setLuogoRitrovo(String luogoRitrovo)
    {
        this.luogoRitrovo=luogoRitrovo;
    }
    
    public void setAnnoRitrovo(int annoRitrovo)
    {
        this.annoRitrovo=annoRitrovo;
    }
   
    public String getDescrizione()
    {
        return "è stato ritrovato a "+luogoRitrovo+" nell'anno "+annoRitrovo;
    
    }
    
    public String getDescrizione(boolean expert)
    {
        if(!expert)
            return getDescrizione();
        else
            return getDescrizione()+i.getDescrizione(expert);
    }
}
