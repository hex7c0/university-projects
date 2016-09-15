package web;

public abstract class Componenti extends Pagine 
{
    protected String alterComponent =""; // alternativa testuale al componente
    protected String strTag = "";
       
    public abstract void setComponent(String s);
    
    public abstract String getComponent();
    
    public String getComponentAlt()
    {
        return alterComponent ;
    }
    
    public String getStrTag()
    {
        return strTag;
    }
}
