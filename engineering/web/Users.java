package web;
import arte.*;

public abstract class Users {
    protected Sede sede;
    protected String nome;
    protected String cognome;       
    protected String userid;
    protected String password;
    protected String email;
    protected int stato;
    protected int admin;

    public Users()
    {
        stato=0;
        admin=0;
    }   

    public void setAnagr(String n, String c)
    {
        cognome = c;
        nome = n;
    }
    
    public String getAnagr()
    {
        return nome +" "+cognome;
    }
    
    public String getUserID()
    {
        return "\n USER ID = "+userid +" : "+password +" Stato = "+stato;
    }
    
    public boolean isAdmin()
    {
        return (admin==1);
    }

    public String getSede()
    {
        return this.sede.getNome();
    }
    
    public Sede getSedeO()
    {
        return sede;
    }
    
    public void setUserId(String id, String pass)
    {
        userid = id;
        password = pass;
        stato = 1;
    }
    
    public int isUser(String uname,String pass)
    {
        if ((uname.equals(this.userid)) && (pass.equals(this.password)) && (this.stato==1))
            return 1;
        return 0;
    }
    
    public boolean isRegistered(String uname)
    {
        if (uname.equals(this.userid))
            return true;
        return false;
    }   
}
