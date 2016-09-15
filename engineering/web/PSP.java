package web;

import java.util.*;

public class PSP extends Visualizzazione
{
    public PSP()
    {
        dispositivo="PSP";
        risoluzione="400x200";
        tagParse = new ArrayList();        
        addTagParse(new HTML());
        addTagParse(new Frame());
        addTagParse(new FStile());
        addTagParse(new Immagine());
    }
}