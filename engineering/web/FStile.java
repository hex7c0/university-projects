package web;

public class FStile extends Componenti
{
    Pagine pag;
    String Style= "\nbody {"+
            "\ncolor: purple;"+
            "\nbackground-color: #d8da3d }";
   
    public FStile()
    {
        alterComponent = "<!-- CSS non gestito -->";
        strTag = "STYLE";
    }
    
    public void setComponent(String s)
    {
        this.Style = s;
    }
    
    public String getComponent()
    {
        String contenuto = "<style type=\"text/css\"> ";
        contenuto += Style +"</style> ";
        return contenuto;
    }
}
