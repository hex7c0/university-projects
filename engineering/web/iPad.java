package web;

import java.util.*;

public class iPad extends Visualizzazione
{
    public iPad()
    {
        dispositivo="iPad";
        risoluzione="450x200";
        tagParse = new ArrayList();
        addTagParse(new HTML());
        addTagParse(new Frame());
        addTagParse(new FStile());
        addTagParse(new Immagine());
    }
}