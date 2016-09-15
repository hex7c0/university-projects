/**
* Bean contenente i dati sulla prova di un concorso
*/
package did;
import java.sql.*;

public class ProvaBean {
	//Definizione dei campi del Bean (variabili private: accessibili solo tramite i metodi get e set)
	private int Nome;	
	private Date Data;
	private Time Ora;
	private String Luogo;
	private String Tipo;
	private int Voto,idc;

	//Definizione del costruttore del Bean
    	public ProvaBean() {
		Nome=0;
		Data=null;
		Ora=null;
		Luogo=null;
		Tipo=null;
		idc=0;
		Voto=0;
    }

    //metodi set
	public void setNome(int d) {
		Nome = d;
    	}

    	public void setData(Date d) {
		Data = d;
    	}

	public void setOra(Time t) {
		Ora = t;
	}

	public void setLuogo(String s) {
		Luogo = s;
    	}

	public void setTipo(String s) {
		Tipo = s;
	}
	
	public void setVoto(int f) {
		Voto = f;
	}
	
	public void setIDC(int f) {
		idc = f;
	}
	

    //metodi get
	public int getNome() {
		return Nome;
	}

	public Date getData() {
		return Data;
	}

	public Time getOra() {
		return Ora;
	}

	public String getLuogo() {
		return Luogo;
	}

	public String getTipo() {
		return Tipo;
	}

	public int getVoto() {
		return Voto;
	}

	public int getIDC() {
		return idc;
	}
}
