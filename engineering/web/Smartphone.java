package web;

import java.util.*;

public class Smartphone extends Visualizzazione
{
    public Smartphone()
    {
        dispositivo="Smartphone";
        risoluzione="400x250";
        tagParse = new ArrayList();        
        addTagParse(new HTML());
        addTagParse(new FStile());
        addTagParse(new Immagine());
        addTagParse(new Applet());
    }
}