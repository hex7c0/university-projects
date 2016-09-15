/**
* Bean per la pagina Esito: contiene i dati di Login del partecipante
*/
package did;

public class EsitoBean {
	//Definizione dei campi del Bean (variabili private: accessibili solo tramite i metodi get e set)
	private String Login;
	private String Password;

	//Definizione del costruttore del Bean
    public EsitoBean() {
		Login=null;
		Password=null;
    }

    //metodi set
    	public void setLogin(String s) {
		Login = s;
    	}

	public void setPassword(String s) {
		Password = s;
	}
	

    //metodi get
	public String getLogin() {
		return Login;
	}

	public String getPassword() {
		return Password;
	}

}
