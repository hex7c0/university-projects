package web;

import java.util.*;

public class NormalView extends Visualizzazione
{
    public NormalView()
    {
        dispositivo="Visualizzazione Normale";
        risoluzione="1024x768";
    
        tagParse = new ArrayList();
        addTagParse(new HTML());
        addTagParse(new Frame());
        addTagParse(new FStile());
        addTagParse(new Immagine());
        addTagParse(new Applet());
    }
}