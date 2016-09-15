package web;


public class Manage implements State
{
    WebSystem ws;
    String funz="";
   
    public Manage(WebSystem Ws)
    {
        this.ws = Ws;
    }
    
    public void Logoff()
    {
    }
    
    public void Manager()
    {
    }
    
    public void Admin()
    {
    }
    
    public void Logon()
    {
    }
    
    public void keyPress(int menu)
    {
        switch (menu)
        {
            case 1 : ws.Aggiungi_opere(); break;
            case 2 : ws.Aggiungi_visite_guidate();break;
            case 3 : ws.Logoff();break;
            case 4 : ws.GestEvSpec();break;
            default: System.out.println("Errore, scelta non disponibile!");
        }
    }
       
    public String print()
    {
        return funz;
    }
    
    public String toString() 
    {
        StringBuffer result = new StringBuffer();
        String funz = "";
        funz += "\n\tElenco Funzioni: ";
        funz += "\n\t1 .Gestione Opere";
        funz += "\n\t2 .Gestione Visite Guidate";        
        funz += "\n\t3 .Logout";
        funz += "\n\t4 .Gestione Eventi Speciali";
        result.append(funz);
        result.append("\n");
        return result.toString();
    }

}