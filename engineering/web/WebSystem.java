package web;

import java.io.*;
import java.util.*;
import arte.*;

public class WebSystem
{
    State login;
    State logout;
    State manage;
    State adm;
    // richiamare le funzioni del sistema WEB pattern STRATEGY + ADAPTER
    
    private Users user;    
    private Ministero ministero;
    String WebFunction;
    String WebContent = "";
    State state = logout;
    
    Visualizzazione view;
       
    public WebSystem(Ministero min)
    {
        ministero=min;
        login = new Login(this);
        logout = new Logout(this);
        manage = new Manage(this);
        adm = new Adm(this);
        setState(logout); 
        WebFunction = "";
    }

    public void keyPress(int menu)
    {
        state.keyPress(menu);
    }
    
    public boolean loginUtente(String uname,String pass)
    {
        Users u;        
        if((u = ministero.getRegistered(uname,pass))!=null)
        {
            
            setWebUser(u);
            return true;
        }
        return false;
    }

    public boolean loginManager(String uname,String pass)
    {
        Manager u;
        if((u = ministero.getManager(uname,pass))!=null)
        {
            setWebUser(u);
            return true;
        }
        return false;
    }

    
    public String WebFoot()
    {
        String foot ="";
        foot += "\n\t___________________________________________________________________\n";
        foot += "\n\tCopyright GRUPPO 28\n";
        return foot;
    }
    
    public String WebShow()
    {
        String head = "";            
        head += "\n\t___________________________________________________________________\n"; 
        head += WebFunction;
        
        return head;
    }

    
    public void setViewer(Visualizzazione v)
    {
        //creato dispositivo per la visualizzazione
        this.view = v;
    }
    
   
    public String toString() {
        
        StringBuffer result = new StringBuffer();
        
        Pagina   p = new Pagina("index.html","Homepage di ACME Inc.");
        Bodypage h = new Bodypage("");
        p.addBody(h);
            //stile
        Componenti stile = new FStile();
        stile.setComponent("Style Script TEXT-Museo Virtuale");
        p.addScript(stile);
        //componenti corpo pagina
        String set_frame = "rows='15%, 70%,15%'";
        Frame frameset_page=new Frame(set_frame);        
        set_frame = "cols='20%, *'";
        Frame setCont = new Frame(set_frame);
        // frame menu
        Pagina   pm = new Pagina("index.html","Homepage di ACME Inc.");
        Bodypage hm = new Bodypage("[SIDE MENU]");
        String menu = "\n\t\t" + state + "";
        hm.addComponet(new HTML(menu));
        pm.addBody(hm);
        pm.addScript(stile);
        menu = view.browse(pm);
       
        // frame titolo
        Pagina   phead = new Pagina("index.html","Homepage di ACME Inc.");
        Bodypage hhead = new Bodypage("[HEAD]");
        
        String head="" 
            + ministero + ""+"\t\t"
            + WebShow() + "";        
        hhead.addComponet(new HTML(head));
        phead.addBody(hhead);
        phead.addScript(stile);
        head = view.browse(phead);
        
        // frame foot
        Pagina   pfoot = new Pagina("index.html","Homepage di ACME Inc.");
        Bodypage hfoot = new Bodypage("[FOOT]");
        String foot="\n\t\t" + WebFoot() + "";
        hfoot.addComponet(new HTML(foot));
        pfoot.addBody(hfoot);
        pfoot.addScript(stile);
        foot = view.browse(pfoot);
        
        // frame contenuto
        //-->>>WebContent
        String content = WebContent;
        Pagina   pcontent = new Pagina("index.html","Homepage di ACME Inc.");
        Bodypage hcontent = new Bodypage("[CONTENT]");
        hcontent.addComponet(new HTML(content));
        pcontent.addBody(hcontent);
        pcontent.addScript(stile);
        content = view.browse(pcontent);      
                 
        setCont.addFramePage(menu,0,0);
        setCont.addFramePage(content,0,0);
        frameset_page.addFramePage(head,0,0);
        frameset_page.addFrameSet(setCont);
        frameset_page.addFramePage(foot,0,0);
        h.BodyFrame(frameset_page);

        // stampa dati del dispositivo utilizzato
        result.append("\n"+view.getDispVis()+"\n");
        
        // inseriamo componenti nella pagina risultante
        
        result.append(view.browse(p));
               
        return result.toString();
    }
    
    
    public void Ricerca_opere()
    {
        // funzione di richiesta per la ricerca
        ArrayList ricerca;
        WebContent = "";  
        WebFunction = "\t\t\t\t\t\t\t\tRicerca Opere\n";
        System.out.print("\n\t\t\t\t\tRicerca Opera\n\n\n");
        String opera="", autore="", museo="", scelta="";//,risp="";
        
        System.out.print("\t\t\t\tNome opera (* -> tutte): ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            opera = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        System.out.print("\t\t\t\tNome autore (* -> tutti): ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            autore = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        System.out.print("\t\t\t\tNome museo (* -> tutti): ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            museo = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        ricerca = ministero.findOpera(museo,opera,autore);
        
        System.out.print("\n\n\t\t ------------------------------------------------\n\n");
        System.out.print("\t\t\t\tRisultato della ricerca:\n\n");
        
        if(ricerca.size() == 0)
            System.out.println("\t\t\tNessun elemento da visualizzare\n\n");
        
        else
        {
            for(int i=0;i<ricerca.size();i++)
            {
                 Opera op = (Opera) ricerca.get(i);
                 System.out.print(""+i+". "+op.getNome()+" - autore: "+op.getAutore()+" - museo: "+op.getMuseo()+"\n\n");

            }
            
            System.out.print("\t\t\t\tApprofondisci un'opera: ");
            try {
                BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
                scelta = is.readLine(); 
            }
            catch (IOException e){
                System.out.println("Errore lettura da utente!!!");
            }
            
            int sc=Integer.parseInt(scelta);
            
          if((sc < 0) || (sc >= ricerca.size()))
          {
                 WebContent += "\n\n\n\nNon è una opzione valida!\n";
          }
          else
          {
            Opera op=(Opera)ricerca.get(sc);
            WebContent +="\n\nNome Opera: "+op.getNome()+"\nAutore: "+op.getAutore()+"\nMuseo: "+op.getMuseo()+"\n\n";
            WebContent +="Informazioni sull'opera:\n\n"+op.getInfo((Utente)user)+"\n\n\n";
          } 
        }
                    
        System.out.println("\n");
        
        WebFunction = "";    
    }
    
    public void Visite_guidate()
    {
        // visite guidate di un museo a richiesta
        WebContent = "";  
        WebFunction = "\t\t\t\t\t\t\t\tVisite Guidate\n";
        ArrayList temp;
      
        System.out.print("\n\t\t\t\t\tVisite Guidate\n\n\n");
        String input="";
        
        System.out.print("\t\t\t\tQuale museo vuole visitare?\n\n");
        temp=ministero.getMusei();
               
        for(int i=0;i<temp.size();i++)
        {
                 Museo mu = (Museo) temp.get(i);
                 System.out.print(""+i+". "+mu.getNome()+"\n\n");

        }
        System.out.print("\t\t\t\tScelta: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            input = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        int scelta=Integer.parseInt(input);
        Museo mu=(Museo)temp.get(scelta);
        
        System.out.print("\n\n\t\t ------------------------------------------------\n\n");
        
        System.out.print("\n\n\t\t\t\tMuseo: "+mu.getNome());
        System.out.print("\n\n\t\t\t\tElenco visite in programma:\n\n");
        temp=mu.getVisite();
        
      if(temp.size() == 0)
             WebContent += "\t\t\t\tNon ci sono visite guidate in programma!\n\n";
      else
      {
        for(int i=0;i<temp.size();i++)
        {
                 Visite vi = (Visite) temp.get(i);
                 if(user == null)
                    WebContent +=""+i+". "+vi.getInfo()+"\n\n";
                 else
                    System.out.print(""+i+". "+vi.getInfo()+"\n\n");

        }
      // se l'utente non è registrato
      if(user != null)
      {
        System.out.print("\t\t\t\tScegli una visita: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            input = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        scelta=Integer.parseInt(input);
        Visite vi=(Visite)temp.get(scelta);
        
        System.out.print("\n\n\t\t ------------------------------------------------\n\n");
        
        System.out.print("\n\n\t\t\t\tVisita selezionata: "+vi.getOrario());
        System.out.print("\n\n\t\t\t\tScegli una opera da visitare:\n\n");
        temp=mu.getOpere();
        for(int i=0;i<temp.size();i++)
        {
                 Opera op = (Opera) temp.get(i);
                 System.out.print(""+i+". "+op.getNome()+"\n\n");

        }
        System.out.print("\t\t\t\tScelta: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            input = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        scelta=Integer.parseInt(input);
        Opera op=(Opera)temp.get(scelta);
        
        System.out.print("\n\n\t\t ------------------------------------------------\n\n");
        
        System.out.print("\n\n\t\t\t\tOpera selezionata: "+op.getNome());
        System.out.print("\n\n\t\t\t\tIn quale giorno?");
       
        System.out.print("\nGiorno: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            input = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        int giorno=Integer.parseInt(input);
        
        System.out.print("\nMese: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            input = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        int mese=Integer.parseInt(input);
        
      if(giorno >= 1 && giorno <= 31 && mese >=1 && mese <= 12)
      {
        
        System.out.print("\n\n\t\t ------------------------------------------------\n\n");
        
        if(mu.checkDisponibilita(giorno,mese,vi) == false)
            WebContent +="\t\tNon c'è disponibilità nel giorno indicato\n\n";
        else
        {
            Prenotazioni pr=new Prenotazioni(vi,op,(Utente)user,giorno,mese);
            mu.addPrenotazione(pr);
            WebContent +="\t\t\t\tPrenotazione effettuata con successo\n\n";
            WebContent +="\tE-Ticket:"+pr.printTicket();
        }
      }
      else
      {
        WebContent +="\t\t\t\tParametri inseriti non validi!\n\n";
      }
    }
   }
        System.out.println("\n");

        WebFunction = "";  
    }

    public void Login()
    {
        //funzione di richiesta UserID e Password
        System.out.print("\t\t\t\tLogin Utente\n");
        System.out.print("\t\t\t________________________\n\n");
        String us = "",pass = "";        
        System.out.print("\t\t\t\tUser ID: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            us = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }            
     
       System.out.print("\t\t\t\tPassword: ");
       try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            pass = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }          
        
       // check credenziali dell'utente, se accettate, andiamo in Login
        WebContent = "";  
        WebFunction = "";
        WebContent = "\t\t\t\t\t\tBenvenuto ";
        if (loginUtente(us,pass) == true) 
        {     
            setState(login);  
            WebContent += user.getAnagr()+"\n";
        }
        else
        {
            if (loginManager(us,pass))
            {
                if (this.user.isAdmin())
                {
                    WebContent += user.getAnagr()+"\n Amministratore del "+user.getSede();
                    setState(adm);                  
                }
                else
                {
                    WebContent += user.getAnagr()+"\n Manager di "+user.getSede();
                    setState(manage);                  
                }
            }
            else
            {    
                WebFunction = "\t\t\t\t\t\t\t\tErrore di login\n";
                WebContent = "";
            }
        }
    }
    
    public void becomeExpert()
    {       
        WebContent = "";
        WebFunction = "\t\t\t\t\t\t\t\tDiventa esperto\n";
        ArrayList temp;
      
        System.out.print("\n\t\t\t\t\tDiventa esperto\n\n\n");
        String input="";
        
        System.out.print("\t\t\t\tIn quale area vuoi diventare esperto?\n\n");
        
        temp=ministero.getlsAree();
        for(int i=0;i<temp.size();i++)
        {
                 Opera po = (Opera) temp.get(i);        
                 System.out.print(""+i+". "+po.getNomeArea()+"\n\n");
        }
   
        System.out.print("\nScelta: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            input = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        int scelta=Integer.parseInt(input);
        Opera po=(Opera)temp.get(scelta);
        Utente usr=(Utente)user;
        usr.setEsperto((AreeCompetenza)po);
        
        WebContent = "Sei diventato esperto in "+po.getNomeArea();
    }
    
    public void Lista_utenti()
    {       
        WebContent = "";
        WebFunction = "\t\t\t\t\t\t\t\tLista degli utenti registrati\n";
        ArrayList temp;
      
        WebContent +="\n\t\t\t\t\tLista degli utenti registrati\n\n\n";
             
        temp=ministero.getlsUtenti();
        for(int i=0;i<temp.size();i++)
        {
                 Utente ut = (Utente) temp.get(i);        
                 WebContent += ""+i+". "+ut.getAnagr()+"\n\n";
        }
          
        WebContent += "Lista utenti terminata";
    }
    
    public void Aggiungi_musei()
    {       
        WebContent = "";
        WebFunction = "\t\t\t\t\t\t\t\tAggiungi un museo\n";
      
        System.out.print("\n\t\t\t\t\tAggiungi un museo\n\n\n");
        String nome="";
             
        System.out.print("\nNome del museo: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            nome = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        ministero.addMuseo(new Museo(nome));
        
        WebContent = "Museo "+nome+" aggiunto correttamente\n";
    }
    
    public void Aggiungi_opere()
    {       
        WebContent = "";
        WebFunction = "\t\t\t\t\t\t\t\tAggiungi opere\n";
        ArrayList temp;
        Manager mger = (Manager)user;
      
        System.out.print("\n\t\t\t\t\tAggiungi opere\n\n\n");
        String nome="",area="",autore="",year="",descrizione="",descrizione_avan="",annrest="",risrest="",annalisi="",risana="",luogo="";
        int anno;
        
        System.out.print("\nScegli un'area di competenza: \n");
        
        temp=ministero.getlsAree();
        for(int i=0;i<temp.size();i++)
        {
                 Opera po = (Opera) temp.get(i);        
                 System.out.print(""+i+". "+po.getNomeArea()+"\n\n");
        }
        System.out.print("\nScelta: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            area = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        int scelta=Integer.parseInt(area);
        
        Opera nuova=(Opera)temp.get(scelta);
        
        System.out.print("\nNome dell'opera: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            nome = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        System.out.print("\nAutore: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            autore = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        System.out.print("\nAnno di ritrovamento: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            year = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        anno=Integer.parseInt(year);
        
        System.out.print("\nLuogo di ritrovamento: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            luogo = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        System.out.print("\nRisultato analisi: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            risana = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        System.out.print("\nAnno analisi: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            annalisi = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        int annoan=Integer.parseInt(annalisi);
        
        System.out.print("\nRisultato restauro: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            risrest = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        System.out.print("\nAnno restauro: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            annrest = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        int annorest=Integer.parseInt(annrest);
        
        nuova.setNome(nome);
        nuova.setAutore(autore);
        InformazioniComuni i = new InformazioniComuni(luogo,anno);
        InformazioniEsperto ie = new InformazioniEsperto();
        ie.setResultAnalisi(risana);
        ie.setDataAnalisi(annoan);
        ie.setResultRestauro(risrest);
        ie.setDataRestauro(annorest);
        i.setInfoExpert(ie);
        nuova.setInfo(i);
        nuova.setMuseo((Museo)mger.getSedeO());
        
        WebContent = "Opera "+nuova.getNome()+" creata correttamente";
    }
    
    public void Aggiungi_visite_guidate()
    {       
        WebContent = "";
        WebFunction = "\t\t\t\t\t\t\t\tAggiungi visite giuidate\n";
        ArrayList temp;
      
        System.out.print("\n\t\t\t\t\tAggiungi visite giuidate\n\n\n");
        String ora="",mini="",guida="";
        
        System.out.print("\n\t\t\t\t\tOrario della visita\n\n\n");
        System.out.print("\nOra: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            ora = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        int orah=Integer.parseInt(ora);
        
        System.out.print("\nMinuti: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            mini = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        int oram=Integer.parseInt(mini);
        
        System.out.print("\nNome della guida: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            guida = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        Visite v = new Visite(orah,oram);
        v.setGuida(guida);
        
        Manager mger = (Manager)user;
        Museo mus=(Museo)mger.getSedeO();
        mus.addVisita(v);
        
        WebContent = "La visita dell'"+v.getOrario()+" è stata creata correttamente";
    }
        
        
    public void Register()
    {
        //funzione di registrzione utente
       
        WebContent = "";  
        WebFunction = "\t\t\t\t\t\t\t\tRegistrazione Utente\n";        
        String cognome="", nome="", userid="", pass="",risp="";
        
        System.out.print("\t\t\t\tCognome: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            cognome = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        System.out.print("\t\t\t\tNome: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            nome = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }

        System.out.print("\t\t\t\tUser ID: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            userid = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        System.out.print("\t\t\t\tPassword: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            pass = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        System.out.print("\t\t\t\tConfermi i dati? (S/N)");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            risp = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        // UPPER CASE
        if ((risp.toLowerCase()).equals("s"))
        {
            Utente usr = new Utente();
            usr.setAnagr(cognome,nome);
            usr.setUserId(userid,pass);            
            ministero.addRegistered(usr);
            ArrayList ust = ministero.getUser();            
            WebContent += "\t\t\tRegistrazione Utente: "+usr.getAnagr()+" terminata con successo\n";
        }    
        WebFunction = "";     
    }
    
    public boolean logout()
    {
        return false;
    }
    
    public int SiteLogoff()
    {
        return 0;
    }
    
    public int SiteLogon()
    {
        return 0;
    }
    
    public void setWebUser(Users u)
    {
        this.user=u;
    }
    
    
    public void Logon()
    {
        state.Logon();
    }
    
    public void Logoff()
    {
        setState(logout);
        WebContent = "\t\t\t\t\t\t\t\tCiao.\n";  
        user=null;
    }
    
    public void Admin()
    {
        state.Admin();
        WebContent = "\t\t\t\t\t\t\t\tCiao Amministratore.\n";        
    }
    
    public void Manager()
    {
        state.Manager();
        WebContent = "\t\t\t\t\t\t\t\tCiao Manager.\n";        
    }
    
    void setState(State state) {
        this.state = state;        
    }

    public State getState() {
        return state;
    }

    public State getLogin() {
        return login;
    }

    public State getLogout() {
        return logout;
    }

    public State getManage() {
        return manage;
    }
    
    public void Esposizioni()
    {        
        // eventi speciali
        WebFunction = "";  
        WebContent = "\n\n\t\t\t\tElenco eventi speciali in programma:\n\n";
        Iterator temp = ministero.getEventi().iterator();
        int vuoto = 1;
        while(temp.hasNext())              
        {
            EventiSpec e = (EventiSpec) temp.next();
            WebContent += e+"\n";
            vuoto = 0;
        }          
        if (vuoto==1)
            WebContent += "\n\n\t\t\tNessuno in programma\n\n";
    }
    
    public void GestEvSpec()
    {
        WebContent = "\n\n\t\t\t\tGestione eventi speciali:\n\n";
        WebContent = "";
        WebFunction = "\t\t\t\t\t\t\t\tAggiungi evento speciale\n";
        ArrayList temp;
      
        System.out.print("\n\t\t\t\t\tAggiungi evento speciale\n\n\n");
        String ora="",mini="",guida="";
        
        System.out.print("\n\t\t\t\t\tOrario dell'evento\n\n\n");
        System.out.print("\nOra: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            ora = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        int orah=Integer.parseInt(ora);
        
        System.out.print("\nMinuti: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            mini = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        int oram=Integer.parseInt(mini);
        
        System.out.print("\nNome della guida: ");
        try {
            BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
            guida = is.readLine(); 
        }
        catch (IOException e){
            System.out.println("Errore lettura da utente!!!");
        }
        
        Visite v = new Visite(orah,oram);
        v.setGuida(guida);
        v.setSpeciale();
        
        
        
        Manager mger = (Manager)user;
        Museo mus=(Museo)mger.getSedeO();
        
        EventiSpec sp1=new EventiSpec(v,mus);
        
        WebContent = ""+sp1.toString()+"è stato creato correttamente";
    }
}
