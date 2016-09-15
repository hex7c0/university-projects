package Codice;

import java.io.*;
import web.*;
import arte.*;

public class TestDriver {

    public static void main(String[] args) {     
        
        Ministero min = new Ministero(" Ministero dei Beni Culturali ");       
        WebSystem website = new WebSystem(min);
        
        iPad ipad = new iPad(); 
        website.setViewer(ipad);          
        initSystem(min);        
        String choose = "";
        int sc = -1;
        while (sc!=0)
        {
            System.out.println(website);    
            System.out.print("Scegli una funzione (0 per uscire): ");
            try {
                BufferedReader is = new BufferedReader(new InputStreamReader(System.in));
                choose = is.readLine(); 
                sc = Integer.parseInt(choose);
                if(sc!=0)
                    website.keyPress(sc);
            }
            catch (IOException e){
                System.out.println("Errore lettura da utente!!!");
            }
        }
        
        System.out.println("Museo Virtuale : Bye!!!");
    }
    
    
    static void initSystem(Ministero m)
    {        
        Museo mu1,mu2,mu3;
        mu1 = new Museo("Museo Diocesano");
        mu2 = new Museo("Museo Egizio");
        mu3 = new Museo("Museo di Storia Spagnola");
        m.addMuseo(mu1);
        m.addMuseo(mu2);
        m.addMuseo(mu3);
        Sala s1,s2,s3;
        s1=new Sala("Opere Pittoriche");
        s2=new Sala("Antico Egitto");
        s3=new Sala("Opere Spagnole");
        Opera o1,o2,o3,o4,o5,o6;
        InformazioniComuni i1,i2,i3,i4,i5,i6;
        InformazioniEsperto ie1,ie2,ie3,ie4,ie5,ie6;
        
        // creo le opere e le loro informazioni
        i1= new InformazioniComuni("Firenze",1290);
        ie1= new InformazioniEsperto();
        ie1.setResultAnalisi("Il dipinto contiene i caratteri tipici della produzione giovanile di Giotto,\ncon una solida resa della volumetria dei personaggi le cui\nattitudini sono più naturali che nella tradizione antecedente;\nil trono è inserito in una prospettiva centrale, formando quasi\nuna nicchia architettonica, che suggerisce un senso della profondità.");
        ie1.setDataAnalisi(1993);
        ie1.setResultRestauro("curato da Paola Bracco presso l'Opificio delle Pietre Dure,\nche pulì la superficie e integrò le lacune, lasciando però visibile con il metodo della selezione cromatica\nla lesione causata da una scheggia nella veste dell'angelo a sinistra.");
        ie1.setDataRestauro(1994);
        i1.setInfoExpert(ie1);
        o1 = new Pittura("Madonna col Bambino");
        o1.setAutore("Giotto");
        o1.setInfo(i1);
        o1.setSala(s1);
        o1.setMuseo(mu1);
        
        i2= new InformazioniComuni("Firenze",1423);
        ie2= new InformazioniEsperto();
        ie2.setResultAnalisi("innovativo era l'uso di un coronamento ad arco a tutto sesto.");
        ie2.setDataAnalisi(1922);
        i2.setInfoExpert(ie2);
        o2 = new Pittura("Trittico Carnesecchi");
        o2.setAutore("Masolino");
        o2.setInfo(i2);
        o2.setSala(s1);
        o2.setMuseo(mu1);
        
        i3= new InformazioniComuni("Firenze",1433);
        ie3= new InformazioniEsperto();
        ie3.setResultAnalisi("La predella è composta da un'unica tavola lignea a fondo oro, in cui sono dipinti tre ovali.\nI personaggi torreggiano rispetto al minuto paesaggio.");
        ie3.setDataAnalisi(1990);
        i3.setInfoExpert(ie3);
        o3 = new Pittura("Predella di Quarate");
        o3.setAutore("Paolo Uccello");
        o3.setInfo(i3);
        o3.setSala(s1);
        o3.setMuseo(mu1);
        
        i4= new InformazioniComuni("Saqqara",1824);
        ie4= new InformazioniEsperto();
        ie4.setResultAnalisi("Questa statua proveniva da una tomba, probabilmente non quella della defunta,\nma quella dell’uomo dal quale lei dipendeva nella vita terrena e ultraterrena. ");
        ie4.setDataAnalisi(1850);
        i4.setInfoExpert(ie4);
        o4 = new Scultura("The Princess Redit");
        o4.setAutore("Sconosciuto");
        o4.setInfo(i4);
        o4.setSala(s2);
        o4.setMuseo(mu2);
        
        i5= new InformazioniComuni("Cairo",1900);
        ie5= new InformazioniEsperto();
        ie5.setResultAnalisi("Il pendente è realizzato in Oro e pietre preziose. Risulta essere un tributo al faraone.\nLe decorazioni sono eseguite minuziosamente.");
        ie5.setDataAnalisi(1920);
        ie5.setResultRestauro("Ricostruzione del pendente sinistro e ricolorazione delle decorazioni rovinate");
        ie5.setDataRestauro(1950);
        i5.setInfoExpert(ie5);
        o5 = new Gioielli("Pendente di Tutankhamon da Tebe");
        o5.setAutore("Arte Egizia");
        o5.setInfo(i5);
        o5.setSala(s2);
        o5.setMuseo(mu2);
        
        i6= new InformazioniComuni("Spagna",1550);
        ie6= new InformazioniEsperto();
        ie6.setResultAnalisi("eseguiti con elegante intreccio di fili di lana e seta, finemente colorate, ad ordito verticale di lana.");
        ie6.setDataAnalisi(1589);
        i6.setInfoExpert(ie6);
        o6 = new Arazzi("Fiamminghi");
        o6.setAutore("Cornelis Tons");
        o6.setInfo(i6);
        o6.setSala(s3);
        o6.setMuseo(mu3);

        Manager adm_min = new Manager("Pippo","Pluto");
        Manager adm_museo1,adm_museo2;
        adm_museo1 = new Manager("Felice","Caccamo");
        adm_museo2 = new Manager("Pippo","Baudo");
        Utente us= new Utente();
        us.setAnagr("giuseppe","malt");
        us.setUserId("gm","pass");
        
        Utente us1= new Utente();
        us1.setAnagr("Mario","Bianchi");
        us1.setUserId("mario","bianchi");
        
        us.setEsperto(new Pittura());
        m.addRegistered(us);
        m.addRegistered(us1);
        m.setAdmin(adm_min); 
        m.addManager(adm_museo1,mu1);
        m.addManager(adm_museo2,mu2);
        
        // creo le guide
        String guida1="Maurizio",guida2="Lino";
        // creo e aggiungo le visite
        Visite v1=new Visite(10,00);
        v1.setGuida(guida1);
        Visite v2=new Visite(15,00);
        v2.setGuida(guida1);
        Visite v3=new Visite(10,00);
        v3.setGuida(guida2);
        Visite v4=new Visite(16,00);
        v4.setGuida(guida1);
        Visite v5=new Visite(14,00);
        v5.setGuida(guida2);
        mu1.addVisita(v1);
        mu1.addVisita(v2);
        mu2.addVisita(v3);
        mu2.addVisita(v4);
        mu3.addVisita(v5);
        // eventi speciali
        Visite v6=new Visite(15,00);
        v6.setGuida(guida2);
        v6.setSpeciale();
        Visite v8=new Visite(17,00);
        v8.setGuida(guida1);
        v8.setSpeciale();
        Visite v7=new Visite(10,00);
        v7.setGuida(guida2);
        v7.setSpeciale();
        EventiSpec sp1=new EventiSpec(v8,mu1);
        EventiSpec sp2=new EventiSpec(v6,mu2);
        EventiSpec sp3=new EventiSpec(v7,mu3);
    }

    
    
}