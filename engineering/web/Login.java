package web;


public class Login implements State
{
    WebSystem ws;
    String funz = "";
    
    public Login(WebSystem Ws)
    {
        this.ws = Ws;
    }
    
    public void Logon()        
    { 
    }
    
    public void Manager()
    {
    }
    
    public void Admin()
    {
    }
    
    public void Logoff()
    {
    }
    
    public void keyPress(int menu)
    {
        switch (menu)
        {
            case 1 : ws.Ricerca_opere(); break;
            case 2 : ws.Visite_guidate();break;
            case 3 : ws.Logoff();break;
            case 4 : ws.becomeExpert();break;
            case 5 : ws.Esposizioni();break;
            default: System.out.println("Errore, scelta non disponibile!");
        }
    }
        
    public String toString() 
    {
        StringBuffer result = new StringBuffer();
        
        funz = "";
        funz += "\n\tElenco Funzioni: ";
        funz += "\n\t1 .Ricerca Opere";
        funz += "\n\t2 .Visite Guidate";
        funz += "\n\t3 .Logout";
        funz += "\n\t4 .Diventa esperto in un'area";
        funz += "\n\t5 .Eventi Speciali";
        
        result.append(funz);
        result.append("\n");
        return result.toString();
    }
}
