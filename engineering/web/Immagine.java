package web;

public class Immagine extends Componenti {
	String url;
    
	public Immagine() 
	{
        alterComponent = "<!-- Immagine non gestita -->";
        strTag = "IMG";
    }
	
    public Immagine(String image) 
    {
        url = "url("+image+")";
        alterComponent = "<!-- Immagine non gestita -->";
        strTag = "IMG";
    }
    
    public void setComponent(String image)
    {
        image = "http://www.google.it/images/nav_logo70.png";
        url = "url("+image+")";
    }
    
    public String getDescription() 
    {
        return "";
    }
    
    public String getComponent()
    {
        String contenuto = "\n<IMG SRC="+url+"/>\n";
        return contenuto;
    }
}
