/**
* Bean contenente le informazioni sul membro della commissione del concorso
*/
package did;

public class CommissioneBean {
	//Definizione dei campi del Bean (variabili private: accessibili solo tramite i metodi get e set)

	private String Nome;
	private String Cognome;
	private String Provenienza;
	private String Ruolo;

	//Definizione del costruttore del Bean
   	public CommissioneBean() {
		Nome=null;
		Cognome=null;
		Provenienza=null;
		Ruolo=null;
    }

    //metodi set
    	public void setNome(String s) {
		Nome = s;
    	}

	public void setCognome(String s) {
		Cognome = s;
	}

	public void setProvenienza(String s) {
		Provenienza = s;
	}
	
	public void setRuolo(String s) {
		Ruolo = s;
	}

    //metodi get
	public String getNome() {
		return Nome;
	}

	public String getCognome() {
		return Cognome;
	}

	public String getProvenienza() {
		return Provenienza;
	}

	public String getRuolo() {
		return Ruolo;
	}
}
