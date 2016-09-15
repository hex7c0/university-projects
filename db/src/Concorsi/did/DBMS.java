/**        DBMS.java        */
package did;

import java.sql.*;
import java.util.*;

/**
 * Questa classe mette a disposizione i metodi per effettuare interrogazioni
 * sulla base di dati.
 */
public class DBMS {
    //Dati di identificazione dell'utente
    private String user = "userlab25";
    private String passwd = "venticinque7M";
	
    /** URL per la connessione alla base di dati e' formato dai seguenti componenti:
     * <protocollo>://<host del server>/<nome base di dati>.
     */
    private String url = "jdbc:postgresql://dbserver.sci.univr.it/dblab25";
    
	/** Driver da utilizzare per la connessione e l'esecuzione delle query. */
    private String driver = "org.postgresql.Driver";

	// definizione delle Query 

	// restituisce i valori di login e password di un partecipante dato il codice fiscale
	private String esito = "SELECT login_pa,password_pa FROM partecipanti WHERE cf_pa=?";
	// restituisce le informazioni sui concorsi non scaduti
	private String bandi = "SELECT id_con,nome_con,data_e_con,data_s_con FROM concorsi WHERE data_s_con>=current_date ORDER BY id_con";
	// restituisce le informazioni di un singolo concorso	
	private String concorso = "SELECT id_con,nome_con,data_e_con,data_s_con FROM concorsi WHERE id_con=?";
	// restituisce le informazioni sul presidente della commissione del concorso	
	private String presidente = "SELECT nome_com,cognome_com,provenienza_com FROM commissione,concorsi WHERE presidente_con=cf_com and id_con=?";
	// restituisce le informazioni sui membri della commissione	
	private String membri = "SELECT nome_com,cognome_com,provenienza_com,ruolo_me FROM commissione,concorsi,membro WHERE id_com_me=cf_com and id_con_me=id_con and id_con=?";
	// restituisce le informazioni sulle prove di un singolo concorso	
	private String prove = "SELECT id_pr,data_pr,ora_pr,luogo_pr,tipo_pr FROM prova,concorsi WHERE concorso_pr=id_con and id_con=?";
	// restituisce le informazioni sul partecipante	e sul risulatato del concorso a seguito del passaggio di login e password
	private String partecipazione = "SELECT cognome_pa,nome_pa,cf_pa,mail_pa,data_pa,provenienza_pa,esito_par FROM partecipanti LEFT JOIN partecipazione ON cf_pa=id_pa_par WHERE login_pa=? and password_pa=?";
	// restituisce le informazioni sulle prove di un concorso svolte da un partecipante	
	private String esitoProve = "SELECT concorso_pr,id_pr,data_pr,ora_pr,luogo_pr,tipo_pr,voto_es FROM partecipanti JOIN partecipazione ON cf_pa=id_pa_par RIGHT JOIN prova ON id_con_par=concorso_pr LEFT JOIN esito ON id_pr_es=id_pr WHERE login_pa=? and password_pa=? ORDER BY id_pr";
	// inserisce nel database una tupla contenente i dati anagrafici del partecipante	
	private String insPartecipante = "INSERT INTO partecipanti (cognome_pa,nome_pa,cf_pa,mail_pa,data_pa,provenienza_pa,login_pa,password_pa) VALUES (?,?,?,?,?,?,?,?)";
	// inserisce nel database una tupla rappresentante la partecipazione del candidato al concorso scelto
	private String iscrizione = "INSERT INTO partecipazione (id_pa_par,id_con_par) VALUES (?,?)";
	// ricava il codice fiscale del partecipante a seguito del passaggio di login e password	
	private String codice = "SELECT cf_pa FROM partecipanti WHERE login_pa=? and password_pa=?";
	// ricava l'id e nome del concorso a cui un partecipante è iscritto
	private String conpar = "SELECT id_con,nome_con FROM concorsi,partecipazione,partecipanti WHERE id_pa_par=cf_pa and id_con=id_con_par and login_pa=? and password_pa=?";
	
    /**
     * Costruttore della classe. Carica i driver da utilizzare per la
     * connessione alla base di dati.
     *
     * @throws ClassNotFoundException Eccezione generata nel caso in cui
     *         i driver per la connessione non siano trovati nel CLASSPATH.
     */
    public DBMS() throws ClassNotFoundException {
		Class.forName(driver);
    }

	//Metodi per la creazione di un bean a partire dal record attuale del ResultSet dato come parametro

	// metodo per creare il bean per la pagina Esito
	private EsitoBean makeEsitoBean(ResultSet rs) throws SQLException {
		EsitoBean bean = new EsitoBean();
		bean.setLogin(rs.getString("login_pa"));
		bean.setPassword(rs.getString("password_pa"));
		return bean;
    }
	
	// metodo per creare il bean per la pagina Partecipante, contiene informazioni sul partecipante e sul concorso
	private PartecipantiBean makePartecipantiBean(ResultSet rs) throws SQLException {
		PartecipantiBean bean = new PartecipantiBean();
		bean.setCognome(rs.getString("cognome_pa"));
		bean.setNome(rs.getString("nome_pa"));
		bean.setCF(rs.getString("cf_pa"));
		bean.setMail(rs.getString("mail_pa"));
		bean.setData(rs.getDate("data_pa"));
		bean.setLuogo(rs.getString("provenienza_pa"));
		bean.setEsito(rs.getString("esito_par"));
		return bean;
    }
	// metodo per creare il bean per la pagina ConcorsoPage, contiene informazioni sul concorso
	private ConcorsoBean makeConParBean(ResultSet rs) throws SQLException {
		ConcorsoBean bean = new ConcorsoBean();
		bean.setID(rs.getInt("id_con"));
		bean.setNome(rs.getString("nome_con"));
		return bean;
    }

	// metodo per creare il bean per la pagina ConcorsoPage, contiene informazioni sul concorso
	private ConcorsoBean makeConcorsoBean(ResultSet rs) throws SQLException {
		ConcorsoBean bean = new ConcorsoBean();
		bean.setID(rs.getInt("id_con"));
		bean.setNome(rs.getString("nome_con"));
		bean.setDataE(rs.getDate("data_e_con"));
		bean.setDataS(rs.getDate("data_s_con"));
		return bean;
    }

	// metodo per creare il bean per la pagina ConcorsoPage, contiene informazioni sul presidente della commissione
	private CommissioneBean makePresidenteBean(ResultSet rs) throws SQLException {   
		CommissioneBean bean = new CommissioneBean();
		bean.setNome(rs.getString("nome_com"));
		bean.setCognome(rs.getString("cognome_com"));
		bean.setProvenienza(rs.getString("provenienza_com"));
		return bean;
    }
	// metodo per creare il bean per la pagina ConcorsoPage, contiene informazioni sul membro della commissione
	private CommissioneBean makeMembroBean(ResultSet rs) throws SQLException {      
		CommissioneBean bean = new CommissioneBean();
		bean.setNome(rs.getString("nome_com"));
		bean.setCognome(rs.getString("cognome_com"));
		bean.setProvenienza(rs.getString("provenienza_com"));
		bean.setRuolo(rs.getString("ruolo_me"));
		return bean;
    }
	// metodo per creare il bean per la pagina Partecipante, contiene informazioni sulla prova e sul suo esito
	private ProvaBean makeEsitoProvaBean(ResultSet rs) throws SQLException {      
		ProvaBean bean = new ProvaBean();
		bean.setIDC(rs.getInt("concorso_pr"));		
		bean.setNome(rs.getInt("id_pr"));
		bean.setData(rs.getDate("data_pr"));
		bean.setOra(rs.getTime("ora_pr"));
		bean.setLuogo(rs.getString("luogo_pr"));
		bean.setTipo(rs.getString("tipo_pr"));
		bean.setVoto(rs.getInt("voto_es"));
		return bean;
     }
    	// metodo per creare il bean per la pagina Concorso, contiene informazioni sulla prova
    	private ProvaBean makeProvaBean(ResultSet rs) throws SQLException {      
		ProvaBean bean = new ProvaBean();
		bean.setNome(rs.getInt("id_pr"));
		bean.setData(rs.getDate("data_pr"));
		bean.setOra(rs.getTime("ora_pr"));
		bean.setLuogo(rs.getString("luogo_pr"));
		bean.setTipo(rs.getString("tipo_pr"));
		return bean;
    }

	
	// Metodo per l'inserimento nella base del candidato
    	public void storeIscrizione(String c,String n,String cf,String m,java.sql.Date d,String l,String lo,String pa)
    	{
    	Connection con = null;
		PreparedStatement pstmt = null;
		try {      
            con = DriverManager.getConnection(url, user, passwd);
			pstmt = con.prepareStatement(insPartecipante);
			pstmt.clearParameters();
			pstmt.setString(1, c);
			pstmt.setString(2, n);
			pstmt.setString(3, cf);
			pstmt.setString(4, m);
			pstmt.setDate(5, d);
			pstmt.setString(6, l);
			pstmt.setString(7, lo);
			pstmt.setString(8, pa);
			pstmt.executeQuery(); 
			con.close();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}

	// Metodo per l'inserimento nella base del partecipante ad un concorso
    	public void storePartecipante(String part,int id)
    	{
    	Connection con = null;
		PreparedStatement pstmt = null;
		try {      
            con = DriverManager.getConnection(url, user, passwd);
			pstmt = con.prepareStatement(iscrizione);
			pstmt.clearParameters();
			pstmt.setString(1, part);
			pstmt.setInt(2, id);
			pstmt.executeQuery(); 
			con.close();
		} catch(Exception e) {
			e.printStackTrace();
		}
	}

	//Metodo per il recupero del codice fiscale di un partecipante
	public Vector getCF(String login,String password) throws SQLException { 
		// Dichiarazione delle variabili
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		Vector result = new Vector();
		try {
			// Tentativo di connessione al database
			con = DriverManager.getConnection(url, user, passwd);
			// Connessione riuscita, ottengo l'oggetto per l'esecuzione
			// dell'interrogazione.
			pstmt = con.prepareStatement(codice); 
			pstmt.clearParameters();
			pstmt.setString(1, login); 
			pstmt.setString(2, password);
			rs=pstmt.executeQuery(); 		
			
			// Memorizzo il risultato dell'interrogazione nel Bean
			while(rs.next())
				result.add(rs.getString("cf_pa"));
		} catch(SQLException sqle) {                /* Catturo le eventuali eccezioni! */
			sqle.printStackTrace();
		} finally {                                 /* Alla fine chiudo la connessione. */
			try {
				con.close();
			} catch(SQLException sqle1) {
				sqle1.printStackTrace();
			}
		}
		return result;
	}

	// Metodo per il recupero delle principali informazioni sul partecipante e sul concorso
	public Vector getPartecipanti(String login,String password) {
		// Dichiarazione delle variabili
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		Vector result = new Vector();
		try {
			// Tentativo di connessione al database
			con = DriverManager.getConnection(url, user, passwd);
			// Connessione riuscita, ottengo l'oggetto per l'esecuzione
			// dell'interrogazione.
			pstmt = con.prepareStatement(partecipazione); 
			pstmt.clearParameters();
			pstmt.setString(1, login); 
			pstmt.setString(2, password);
			rs=pstmt.executeQuery(); 		
			
			// Memorizzo il risultato dell'interrogazione nel Bean
			while(rs.next())
				result.add(makePartecipantiBean(rs));
		} catch(SQLException sqle) {                /* Catturo le eventuali eccezioni! */
			sqle.printStackTrace();
		} finally {                                 /* Alla fine chiudo la connessione. */
			try {
				con.close();
			} catch(SQLException sqle1) {
				sqle1.printStackTrace();
			}
		}
		return result;
	}

	public Vector getConPar(String login,String password) {
		// Dichiarazione delle variabili
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		Vector result = new Vector();
		try {
			// Tentativo di connessione al database
			con = DriverManager.getConnection(url, user, passwd);
			// Connessione riuscita, ottengo l'oggetto per l'esecuzione
			// dell'interrogazione.
			pstmt = con.prepareStatement(conpar); 
			pstmt.clearParameters();
			pstmt.setString(1, login); 
			pstmt.setString(2, password);
			rs=pstmt.executeQuery(); 		
			
			// Memorizzo il risultato dell'interrogazione nel Bean
			while(rs.next())
				result.add(makeConParBean(rs));
		} catch(SQLException sqle) {                /* Catturo le eventuali eccezioni! */
			sqle.printStackTrace();
		} finally {                                 /* Alla fine chiudo la connessione. */
			try {
				con.close();
			} catch(SQLException sqle1) {
				sqle1.printStackTrace();
			}
		}
		return result;
	}
	
	// Metodo per il recupero dell'esito della registrazione del partecipante al servizio
	public Vector getEsito(String CodFiscale) {
		// Dichiarazione delle variabili
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		Vector result = new Vector();
		try {
			// Tentativo di connessione al database
			con = DriverManager.getConnection(url, user, passwd);
			// Connessione riuscita, ottengo l'oggetto per l'esecuzione
			// dell'interrogazione.
			pstmt = con.prepareStatement(esito); 
			pstmt.clearParameters();
			pstmt.setString(1, CodFiscale); 
			rs=pstmt.executeQuery(); 		
			
			// Memorizzo il risultato dell'interrogazione nel Bean
			while(rs.next())
				result.add(makeEsitoBean(rs));
		} catch(SQLException sqle) {                /* Catturo le eventuali eccezioni! */
			sqle.printStackTrace();
		} finally {                                 /* Alla fine chiudo la connessione. */
			try {
				con.close();
			} catch(SQLException sqle1) {
				sqle1.printStackTrace();
			}
		}
		return result;
	}
	
	// Metodo per il recupero delle informazioni sul concorso
	public Vector getConcorso(int idConcorso) {
		// Dichiarazione delle variabili
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		Vector result = new Vector();
		try {
			// Tentativo di connessione al database
			con = DriverManager.getConnection(url, user, passwd);
			// Connessione riuscita, ottengo l'oggetto per l'esecuzione
			// dell'interrogazione.
			pstmt = con.prepareStatement(concorso); 
			pstmt.clearParameters();
			pstmt.setInt(1, idConcorso); 
			rs=pstmt.executeQuery(); 		
			
			// Memorizzo il risultato dell'interrogazione nel Bean
			while(rs.next())
				result.add(makeConcorsoBean(rs));
		} catch(SQLException sqle) {                /* Catturo le eventuali eccezioni! */
			sqle.printStackTrace();
		} finally {                                 /* Alla fine chiudo la connessione. */
			try {
				con.close();
			} catch(SQLException sqle1) {
				sqle1.printStackTrace();
			}
		}
		return result;
	}
	
	//Metodo per il recupero delle principali informazioni sui bandi di concorso non scaduti
	public Vector getBandi() {
		// Dichiarazione delle variabili
		Connection con = null;
		Statement stmt = null;
		ResultSet rs = null;
		Vector result = new Vector();
		try {
			// Tentativo di connessione al database
			con = DriverManager.getConnection(url, user, passwd);
			// Connessione riuscita, ottengo l'oggetto per l'esecuzione dell'interrogazione.
			stmt = con.createStatement();
			// Eseguo l'interrogazione desiderata
			rs = stmt.executeQuery(bandi);
			// Memorizzo il risultato dell'interrogazione nel Vector
			while(rs.next())
				result.add(makeConcorsoBean(rs));
		} catch(SQLException sqle) {                /* Catturo le eventuali eccezioni! */
			sqle.printStackTrace();
		} finally {                                 /* Alla fine chiudo la connessione. */
			try {
				con.close();
			} catch(SQLException sqle1) {
				sqle1.printStackTrace();
			}
		}
		return result;
    }
	
	// Metodo per il recupero delle informazioni sulle prove di un concorso
	public Vector getProve(int idConcorso) {
		// Dichiarazione delle variabili
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		Vector result = new Vector();
		try {
			// Tentativo di connessione al database
			con = DriverManager.getConnection(url, user, passwd);
			// Connessione riuscita, ottengo l'oggetto per l'esecuzione
			// dell'interrogazione.
			pstmt = con.prepareStatement(prove); 
			pstmt.clearParameters();
			pstmt.setInt(1, idConcorso); 
			rs=pstmt.executeQuery(); 		
			
			// Memorizzo il risultato dell'interrogazione nel Bean
			while(rs.next())
				result.add(makeProvaBean(rs));
		} catch(SQLException sqle) {                /* Catturo le eventuali eccezioni! */
			sqle.printStackTrace();
		} finally {                                 /* Alla fine chiudo la connessione. */
			try {
				con.close();
			} catch(SQLException sqle1) {
				sqle1.printStackTrace();
			}
		}
		return result;
	}
	
	// Metodo per il recupero delle informazioni sull'esito delle prove svolte da un partecipante
	public Vector getEsitoProve(String login,String password) {
		// Dichiarazione delle variabili
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		Vector result = new Vector();
		try {
			// Tentativo di connessione al database
			con = DriverManager.getConnection(url, user, passwd);
			// Connessione riuscita, ottengo l'oggetto per l'esecuzione
			// dell'interrogazione.
			pstmt = con.prepareStatement(esitoProve); 
			pstmt.clearParameters();
			pstmt.setString(1, login); 
			pstmt.setString(2, password);
			rs=pstmt.executeQuery(); 		
			
			// Memorizzo il risultato dell'interrogazione nel Bean
			while(rs.next())
				result.add(makeEsitoProvaBean(rs));
		} catch(SQLException sqle) {                /* Catturo le eventuali eccezioni! */
			sqle.printStackTrace();
		} finally {                                 /* Alla fine chiudo la connessione. */
			try {
				con.close();
			} catch(SQLException sqle1) {
				sqle1.printStackTrace();
			}
		}
		return result;
	}
	
	// Metodo per il recupero delle informazioni sul presidente della commissione del concorso
	public Vector getPresidente(int idConcorso) {
		// Dichiarazione delle variabili
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		Vector result = new Vector();
		try {
			// Tentativo di connessione al database
			con = DriverManager.getConnection(url, user, passwd);
			// Connessione riuscita, ottengo l'oggetto per l'esecuzione
			// dell'interrogazione.
			pstmt = con.prepareStatement(presidente); 
			pstmt.clearParameters();
			pstmt.setInt(1, idConcorso); 
			rs=pstmt.executeQuery(); 		
			
			// Memorizzo il risultato dell'interrogazione nel Bean
			while(rs.next())
				result.add(makePresidenteBean(rs));
		} catch(SQLException sqle) {                /* Catturo le eventuali eccezioni! */
			sqle.printStackTrace();
		} finally {                                 /* Alla fine chiudo la connessione. */
			try {
				con.close();
			} catch(SQLException sqle1) {
				sqle1.printStackTrace();
			}
		}
		return result;
	}
	
		// Metodo per il recupero delle informazioni sui membri della commissione del concorso
	public Vector getMembri(int idConcorso) {
		// Dichiarazione delle variabili
		Connection con = null;
		PreparedStatement pstmt = null;
		ResultSet rs = null;
		Vector result = new Vector();
		try {
			// Tentativo di connessione al database
			con = DriverManager.getConnection(url, user, passwd);
			// Connessione riuscita, ottengo l'oggetto per l'esecuzione
			// dell'interrogazione.
			pstmt = con.prepareStatement(membri); 
			pstmt.clearParameters();
			pstmt.setInt(1, idConcorso); 
			rs=pstmt.executeQuery(); 		
			
			// Memorizzo il risultato dell'interrogazione nel Bean
			while(rs.next())
				result.add(makeMembroBean(rs));
		} catch(SQLException sqle) {                /* Catturo le eventuali eccezioni! */
			sqle.printStackTrace();
		} finally {                                 /* Alla fine chiudo la connessione. */
			try {
				con.close();
			} catch(SQLException sqle1) {
				sqle1.printStackTrace();
			}
		}
		return result;
	}
}
