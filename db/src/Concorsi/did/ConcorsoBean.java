/**
* Bean per la tabella (campi principali) Concorso
*/
package did;
import java.sql.*;

public class ConcorsoBean {
	//Definizione dei campi del Bean (variabili private: accessibili solo tramite i metodi get e set)
	private int ID;
	private String Nome;
	private Date DataE;
	private Date DataS;

	//Definizione del costruttore del Bean
    public ConcorsoBean() {
		ID=0;
		Nome=null;
		DataE=null;
		DataS=null;
    }

    //metodi set
    	public void setID(int d) {
		ID = d;
    	}

	public void setNome(String s) {
		Nome = s;
	}

	public void setDataE(Date g) {
		DataE = g;
	}

	public void setDataS(Date g) {
		DataS = g;
	}
	
    //metodi get
	public int getID() {
		return ID;
	}

	public String getNome() {
		return Nome;
	}

	public Date getDataE() {
		return DataE;
	}

	public Date getDataS() {
		return DataS;
	}
}
