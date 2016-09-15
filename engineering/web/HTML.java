package web;

public class HTML extends Componenti
{
    String contenuto = "";
    
    public HTML()
    {
        strTag = "BODY";
    }

    public HTML(String h)
    {
        contenuto=h;
        strTag = "BODY";
    }
    
    public String getDescription() 
    {
        return " Testo HTML";
    }
    
    public void setComponent(String s)
    {
        this.contenuto = s;
    }

    public String getComponent()
    {
        return contenuto;
    }
}
