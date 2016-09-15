import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import did.*;

/**
 * Questa classe gestisce le richieste riguardanti le ricerche all'interno della
 * base di dati. Risponde solamente a richieste HTTP di tipo GET. I possibili
 * parametri che vengono considerati e le relative azioni effettuate sono le
 * seguenti:
 * <br>
 * <ol>
 *   <li>parametro ps="": viene visualizzata la homepage con una descrizione dell'ufficio e l'elenco dei concorsi disponibili;</li>
 *   <li>parametro ps="esito", id, Login e Password: viene visualizzato l'esito dell'iscrizione del partecipante al concorso;</li>
 *   <li>parametro ps="esito", Cognome, Nome, CF, Mail, Luogo, giorno, mese, anno: viene visualizzato l'esito dell'iscrizione del partecipante al servizio;</li>
 *   <li>parametro ps="domanda", id: viene visualizzato la form per l'iscrizione del partecipante al concorso;</li>
 *   <li>parametro ps="iscrizione": viene visualizzato la form per l'iscrizione del partecipante al servizio;</li>
 *   <li>parametro ps="riepilogo", login_pa, password_pa: viene visualizzata la pagina di riepilogo contentente i dati del concorso e delle prove
 *       svolte dal partecipante;</li>
 *   <li>parametro ps="concorso", id: viene visualizzata la pagina contenente i dati sul concorso, le prove che lo compongono e i membri della sua commissione;</li>
 * </ol>
 */
public class main extends HttpServlet {
    /**
     * Questo metodo risponde alle richieste HTTP di tipo GET. Elabora le richieste, impostando
     * gli eventuali attributi necessari, e ridirige la visualizzazione alle pagine jsp relative.
     *
     * @param request Oggetto HttpServletRequest dal quale ottenere informazioni circa la
     *                richiesta effettuata.
     * @param response Oggetto HttpServletResponse per l'invio delle risposte.
     */
    public void doGet(HttpServletRequest request, HttpServletResponse response)
	throws IOException, ServletException {

		//Definizione del parametro della servlet
		String ps = "";
		//Dichiaro l'oggetto Dispatcher necessario per passare il controllo ad una JSP o una pagina HTML
		RequestDispatcher rd = null;
	
		if (request.getParameter("ps") != null) {// Ottengo se presente il parametro 'ps'
			ps = request.getParameter("ps");
		}
	
		try {
			// Oggetto per l'interazione con il Database
			DBMS dbms = new DBMS();
			if (ps.equals("")) {	// visualizzo la Homepage
				//Delego l'esecuzione della query alla classe di interazione con il DB
				//Recupero il risultato della query come un Vector contenente dei bean
				Vector bandi = dbms.getBandi();
				//Aggiungo il Vector come attributo della richiesta HTTP
				request.setAttribute("bandi",bandi);
				//Preparo il Dispatcher
				rd = request.getRequestDispatcher("../Home.jsp");
				//Passo il controllo alla JSP
				rd.forward(request,response);	
			}

			if (ps.equals("esito")) { // visualizzo l'esito dell'iscrizione al servizio (o concorso)
			    String check="iscritto";
			    // se è stato passato il parametro "id", la registrazione sarà ad un concorso
							    
			    if (request.getParameter("id") != null) 
			    {	
				String Login = "";
				String Password = "";
				String id = request.getParameter("id");
				if (request.getParameter("Login") != null) {
					Login = request.getParameter("Login");
				}
				if (request.getParameter("Password") != null) {
					Password = request.getParameter("Password");
				}
				Vector con = dbms.getConPar(Login,Password);
				// se il partecipante non è già iscritto al concorso, lo iscrivo
				if(con.size()==0)
				{
					Vector cf = dbms.getCF(Login,Password);
					if(cf.size()==0)
						check="no"; 
					else {
						String codice=(String)cf.get(0);	
						// inserisco nel db la nuova tupla --> partecipante iscritto al concorso
						dbms.storePartecipante(codice,Integer.parseInt(id));
						check="iscrizione";
					}					
				}
				// altrimenti non lo iscrivo 2 volte
				else 
					check="vuoto";

			     }	
		    	     // se non è stato passato il parametro "id", la registrazione sarà al servizio
			     else {	
				String Cognome = "";	//Recupero i dati inseriti nella form
				String Nome = "";
				String CF = "";
				String Mail = "";
				String Anno = "";
				String Mese = "";
				String Giorno = "";
				String Luogo = "";
				if (request.getParameter("Cognome") != null) {
					Cognome = request.getParameter("Cognome");
				}
				if (request.getParameter("Nome") != null) {
					Nome = request.getParameter("Nome");
				}
				if (request.getParameter("CF") != null) {
					CF = request.getParameter("CF");
				}
				if (request.getParameter("Mail") != null) {
					Mail = request.getParameter("Mail");
				}
				if (request.getParameter("Luogo") != null) {
					Luogo = request.getParameter("Luogo");
				}
				if (request.getParameter("giorno") != null) {
					Giorno = request.getParameter("giorno");
				}
				if (request.getParameter("mese") != null) {
					Mese = request.getParameter("mese");
				}
				if (request.getParameter("anno") != null) {
					Anno = request.getParameter("anno");
				}
				// genero la data in formato accettato da postgresql
				java.sql.Date d=java.sql.Date.valueOf(Anno+"-"+Mese+"-"+Giorno);
				// genero la login come "nome.cognome"
				String loginP=""+Nome+"."+Cognome;
				// genero la password come "cognomeAnno"
				String passwordP=""+Cognome+Anno;
				
				// inserisco nel db la nuova tupla --> partecipante iscritto al servizio
				dbms.storeIscrizione(Cognome,Nome,CF,Mail,d,Luogo,loginP,passwordP);
				//Delego l'esecuzione della query alla classe di interazione con il DB
				//Recupero il risultato della query come un Vector contenente dei bean
				Vector esito = dbms.getEsito(CF);
				//Aggiungo il Vector come attributo della richiesta HTTP
				request.setAttribute("esito",esito);	
			    } 
				//Preparo il Dispatcher						 
				request.setAttribute("vuoto",check);
				rd = request.getRequestDispatcher("../Esito.jsp");
				//Passo il controllo alla JSP
				rd.forward(request,response);	
			}			

			if (ps.equals("domanda")) { //visualizzo la form per l'iscrizione al concorso
				String id = "";
				if (request.getParameter("id") != null) {
					id = request.getParameter("id");
				}
				request.setAttribute("id",id);
				//Preparo il Dispatcher
				rd = request.getRequestDispatcher("../Domanda.jsp");
				//Passo il controllo alla JSP
				rd.forward(request,response);	
			}

			if (ps.equals("iscrizione")) { //visualizzo la form per l'iscrizione al servizio
				//Preparo il Dispatcher
				rd = request.getRequestDispatcher("/html/Iscrizione.html");
				//Passo il controllo alla JSP
				rd.forward(request,response);	
			}

			if (ps.equals("riepilogo")) { // visualizzo la pagina di riepilogo dei concorsi e delle prove svolte dal partecipante
				String Login = "";
				String Password = "";
				if (request.getParameter("login_pa") != null) {
					Login = request.getParameter("login_pa");
				}
				if (request.getParameter("password_pa") != null) {
					Password = request.getParameter("password_pa");
				}
				//Delego l'esecuzione della query alla classe di interazione con il DB
				//Recupero il risultato della query come un Vector contenente dei bean
				Vector riepilogo = dbms.getPartecipanti(Login,Password);
				Vector prove = dbms.getEsitoProve(Login,Password);
				Vector concorso = dbms.getConPar(Login,Password);
				//Aggiungo il Vector come attributo della richiesta HTTP
				request.setAttribute("partecipante",riepilogo);
				request.setAttribute("prove",prove);
				request.setAttribute("concorso",concorso);
				//Preparo il Dispatcher
				rd = request.getRequestDispatcher("../Partecipante.jsp");
				//Passo il controllo alla JSP
				rd.forward(request,response);	
			}

			if (ps.equals("concorso")) { // visualizzo la pagina contenente le informazioni sul concorso
				String id = "";
				if (request.getParameter("id") != null) {
					id = request.getParameter("id");
				}
				//Delego l'esecuzione della query alla classe di interazione con il DB
				//Recupero il risultato della query come un Vector contenente dei bean
				Vector presidente = dbms.getPresidente(Integer.parseInt(id));
				Vector membri = dbms.getMembri(Integer.parseInt(id));
				Vector prove = dbms.getProve(Integer.parseInt(id));
				Vector concorso = dbms.getConcorso(Integer.parseInt(id));
				//Aggiungo il Vector come attributo della richiesta HTTP
				request.setAttribute("presidente",presidente);
				request.setAttribute("membri",membri);
				request.setAttribute("prove",prove);
				request.setAttribute("concorso",concorso);
				//Preparo il Dispatcher
				rd = request.getRequestDispatcher("../ConcorsoPage.jsp");
				//Passo il controllo alla JSP
				rd.forward(request,response);	
			}
				
			
		} catch(Exception e) {  //Gestisco eventuali eccezioni visualizzando lo stack delle chiamate
			e.printStackTrace();
		}
    }
}
