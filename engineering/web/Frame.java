package web;

import java.util.*;

public class Frame extends Componenti 
{
    Pagine pag;
    int border=0, spacing=0, margin=0;
    String set = "24%,*";
    ArrayList frame;

    public Frame() 
    {
        frame = new ArrayList();        
        alterComponent = "<!-- Frame non gestito -->";
        strTag = "FRAME";
    }
    
    public Frame(String setting) 
    {
        frame = new ArrayList();        
        alterComponent = "<!-- Frame non gestito -->";
        strTag = "FRAME";
        this.set = setting;
    }
    
    public void addFramePage(String html, int marginw, int marginh)
    {
        String frame_string = "\n   <FRAME name=\"textbereich\"  marginwidth="+marginw+"  marginheight="+marginw+">" ;
        frame_string += "\n  "+html+"";
        frame_string += "  </FRAME>\n";
        frame.add(frame_string);
    }
        
    public void setComponent(String s)
    {
        s="";
    }
    
    public void addFrameSet(Frame frameset)
    {
        String frame_string = frameset.getComponent(); ;
        frame.add(frame_string);
    }
    
    public String getComponent()
    {
        contenuto = "\n<FRAMESET "+set+">";
        if (frame!=null)
        {
            for (int i=0; i< frame.size(); i++)
            {
                String  f = (String) frame.get(i);
                contenuto += "\n" + f;
            }
        }
        contenuto += "</FRAMESET>\n"; 

        return contenuto;
    }
}