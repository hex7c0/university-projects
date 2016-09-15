package web;

public class Applet extends Componenti 
{
    String applet= "MyApplet.class", altern="Ci sono";
    int width=100,height=100;
    
    public Applet() 
    {
        alterComponent = "<!-- Applet non gestito -->";
        strTag = "APPLET";        
    }

    
    public Applet(String applet_name) 
    {
        if (applet_name!="")
            applet = applet_name;
        alterComponent = "<!-- Applet non gestito -->";
        strTag = "APPLET";
    }

    public String getDescription() 
    {
        return "";
    }
    
    public void setComponent(String s)
    {
        s="";
    }

    
    public void setApplet(String applet_name,int w,int h)
    {
        
        applet = applet_name;
        width = w;
        height = h;
        // parametri di TEST
        applet = "MyApplet.class";
        width=100;
        height=100;
    }

    public String getComponent()
    {
        String contenuto = "<APPLET CODE="+applet+" WIDTH="+width+" HEIGHT="+height+">"+
                            "<PARAM NAME=TEXT VALUE="+altern+">"+
                            "<P>Hi There<P>"+
                            "</APPLET>";
        return contenuto;
    }    
}
