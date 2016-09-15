/**
* Bean per la tabella (campi principali) Partecipanti
*/
package did;
import java.sql.*;

public class PartecipantiBean {
	//Definizione dei campi del Bean (variabili private: accessibili solo tramite i metodi get e set)
	private String Cognome;
	private String Nome;
	private String CF;
	private String Mail;
	private Date Data;
	private String Luogo;
	private String Esito;

	//Definizione del costruttore del Bean
    public PartecipantiBean() {
		Cognome = null;
		Nome = null;
		CF = null;
		Mail = null;
		Data = null;
		Luogo = null;
		Esito = null;
    }

    //metodi set
   
	public void setCognome(String s) {
		Cognome = s;
	}
	
	public void setNome(String s) {
		Nome = s;
	}

	public void setCF(String s) {
		CF = s;
	}

	public void setMail(String s) {
		Mail = s;
	}

	public void setData(Date d) {
		Data = d;
	}
	
	public void setLuogo(String s) {
		Luogo = s;
	}
	
	public void setEsito(String s) {
		Esito = s;
	}


    //metodi get

	public String getCognome() {
		return Cognome;
	}

	public String getNome() {
		return Nome;
	}

	public String getCF() {
		return CF;
	}

	public String getMail() {
		return Mail;
	}

	public Date getData() {
		return Data;
	}
	
	public String getLuogo() {
		return Luogo;
	}
	
	public String getEsito() {
		return Esito;
	}
}
