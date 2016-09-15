package web;

public class Adm implements State
{
    WebSystem ws;
    String funz="";
    
    public Adm(WebSystem Ws)
    {
        this.ws = Ws;
    }

    public void keyPress(int menu)
    {
        switch (menu)
        {
            case 1 : ws.Lista_utenti(); break;
            case 2 : ws.Aggiungi_musei();break;
            case 3 : ws.Logoff();break;
            default: System.out.println("Errore, scelta non disponibile!");
        }
    }
    
    public void Logon()
    {
    }
    
    public void Admin()
    {
    }
    
    public void Logoff()
    {
    }
    
    public void Manager()
    {
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
        funz += "\n\t1 .Gestione Utenti";
        funz += "\n\t2 .Aggiungi un Museo";        
        funz += "\n\t3 .Logout";
        result.append(funz);
        result.append("\n");
        return result.toString();
    }
}
