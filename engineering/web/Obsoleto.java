package web;

import java.util.*;

public class Obsoleto extends Visualizzazione
{
    boolean val;
    
    public Obsoleto()
    {
        dispositivo="Sistema obsoleto - Browser Testuale Lynx";
        risoluzione="80x25";
        tagParse = new ArrayList();
        addTagParse(new HTML());
        addTagParse(new Frame());
    }
}