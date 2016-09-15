package web;


public class Logout implements State
{
    WebSystem ws;
    String funz = "";
    
    public Logout(WebSystem Ws)
    {
        this.ws = Ws;
    }
    
    public void Manager()
    {
    }
    
    public void Logoff()
    {
    }
    
    public void Admin()
    {
    }
    
    public String print()
    {
        return funz;
    }

    public void Logon()        
    {
        ws.setState(ws.getLogin());
    }
    
    public void Manage()
    {
    }
    
    public void keyPress(int menu)
    {
        switch (menu)
        {
            case 1 : ws.Ricerca_opere(); break;
            case 2 : ws.Visite_guidate();break;
            case 3 : ws.Login();break;
            case 4 : ws.Register();break;
            case 5 : ws.Esposizioni();break;
            default: System.out.println("Errore, ("+menu+")  scelta non disponibile!");
        }
    }
            
    public String toString() 
    {
        StringBuffer result = new StringBuffer();
        funz = "";       
        funz += "\n\tElenco Funzioni: ";
        funz += "\n\t1 .Ricerca Opere";
        funz += "\n\t2 .Visite Guidate";
        funz += "\n\t3 .Login Utente";
        funz += "\n\t4 .Registrazione Utente";
        funz += "\n\t5 .Eventi Speciali";
        result.append(funz);
        result.append("\n");
        return result.toString();
    }
}
