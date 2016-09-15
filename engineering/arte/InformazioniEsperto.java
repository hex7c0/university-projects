package arte;

public class InformazioniEsperto implements Informazioni
{
    private String resultAnalisi;
    private String resultRestauro;
    private int dataAnalisi;
    private int dataRestauro;
    
    public InformazioniEsperto()
    {
        resultAnalisi=null;
        resultRestauro=null;
        dataAnalisi=0;
        dataRestauro=0;
    }
        
    public void setResultAnalisi(String resultAnalisi)
    {
        this.resultAnalisi=resultAnalisi;
    }
    
    public void setResultRestauro(String resultRestauro)
    {
        this.resultRestauro=resultRestauro;
    }
    
    public void setDataAnalisi(int dataAnalisi)
    {
        this.dataAnalisi=dataAnalisi;
    }
    
    public void setDataRestauro(int dataRestauro)
    {
        this.dataRestauro=dataRestauro;
    }
       
    public String getDescrizione(boolean expert)
    {
        String infoExpert;
        
        infoExpert = "\n-------------------------------------------------\nInformazioni supplementari\n";
        infoExpert += "\nAnalisi chimiche: ";
        if(dataAnalisi == 0)
            infoExpert += "non sono state eseguite sull'oggetto\n";
        else
            infoExpert += "le analisi sono state eseguite il giorno: "+dataAnalisi+"\nResoconto analisi: "+resultAnalisi;
            
        infoExpert += "\nRestauro: ";
        if(dataRestauro == 0)
            infoExpert += "non è stato eseguito sull'oggetto\n";
        else
            infoExpert += "il restauro è stato eseguito il giorno: "+dataRestauro+"\nResoconto restauro: "+resultRestauro;
            
        return infoExpert;
    }
}