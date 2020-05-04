//#include "commons.h"
//#include "funz_rubrica.h"

// =====================================================================================================
// FUNZIONI DI SOTTOMENU 5 - Operazioni su Rubrica  ====================================================
// =====================================================================================================


// Sottomenu Rubrica - 0 Stampa del sottomenu
void menuRubrica() {
    cout << "\nMenu Rubrica";
    cout << "\n************\n\n";
    cout << "1) STAMPA la rubrica" << endl;
    cout << "2) ORDINA la rubrica" << endl;
    cout << "3) SALVA la rubrica su FILE" << endl;
    cout << "4) CANCELLA tutta la rubrica" << endl;
    cout << "5) Torna al menu principale" << endl;
}



// Sottomenu Rubrica - 1 Stampa la rubrica intera
void stampaRubrica(Contatto *head) {

    // Formattazione a tabella (prossima versione...)
    //cout << "| ID\n| Nome\t\t| Cognome\n\n| Numero Tel\t| Email\t\t| ";

    Contatto *scorri = head;

    while(scorri!=nullptr) {
        
        stampaContatto(scorri,1);
        scorri=scorri->next;
    }

    cout << "\n+-----------------------------------------------+\n";
}



// SottoMenu Rubrica - 2 Ordina Rubrica
void ordinaRubrica(Rubrica *rub) {
    // DEVE PREVEDERE LA SCELTA MULTIPLA
    
    bool continua=true;
    //Contatto *scorri = rub->head;

    /*
    do {        
		esci = true;
		while (scorri->next!=nullptr) {
            Contatto *conf2 = scorri;
            scorri=scorri->next;
            // Debug:
            cout << "Confronto tra " << conf2->id << " e " << scorri->id << endl;
            cout << "Confronto tra S2:" << conf2->cognome << " e S1:" << scorri->cognome << endl;
            if ((conf2->cognome) > (scorri->cognome)) {
                Contatto *tmp = conf2;
                conf2 = scorri;
                scorri = tmp;
                esci = false;
                cout << "scambiati valori S2: " << conf2->cognome << " - S: " << scorri->cognome << endl;
            }
            //scorri = scorri->next;
            cout << "scorri: " << scorri->id << endl;
            cout << "Confronto dopo scambio\nS2: " << conf2->cognome << "\nS: " << scorri->cognome << endl;
		}
	} while (esci);
    */
   int loop=0;

    
	do {      
        loop++;  
		continua = false;
        Contatto *scorri = rub->head;
        if(loop<101)
		while (scorri->next!=nullptr) {
            Contatto *conf1 = scorri->next;
            Contatto *conf2 = scorri;
            // Debug:
            cout << loop << "\n*******************************************************\n\n";
            cout << "scorri: " << scorri << "\nconf1: " << conf1 << "\nconf2: " << conf2 << endl;
            //cout << "Confronto tra " << conf2->id << " e " << conf1->id << endl;
            //cout << "Confronto tra \nconf2:" << conf2->cognome << "\ne\nconf1:" << conf1->cognome << endl;
            if ((conf2->cognome) > (conf1->cognome)) {
                Contatto *tmp = conf2;
                conf2 = conf1;
                conf1 = tmp;
                continua = true;
                cout << "scambiati valori conf2: " << conf2->cognome << " - conf1: " << conf1->cognome << endl;
            }
           
            scorri = scorri->next;
            //cout << "scorri: " << scorri->id << endl;
            //cout << "Confronto dopo scambio\nconf2: " << conf2->cognome << "\nconf1: " << scorri->cognome << endl;
		}
        rub->tail=scorri; // all'ultimo passaggio scorri dovrebbe essere la coda (ordinata)
	} while (continua);
    
    

}


// Sotto Menu Rubrica - 3 Salva Rubrica su File
bool salvaRubrica(Rubrica *rub,string file,int rewrite=0) {

    bool ret=true; // rubrica salvata di default
    int count=0;
    char sep=';';
    fstream fs;
    Contatto *c;

    c = rub->head;

    if(rewrite==0 && nodoSalvato!=nullptr) {
        cout << "\n *** Aggiornamento file in corso ***\n";
        fs.open(file, ios::app);
        // se ho gia salvato dei contatti riparto dall'ultimo punto salvato
        // altrimenti parto dall'inizi (head)
        c = nodoSalvato;//->next; 
    }
    else {
        //cout << "\n *** Scrittura file in corso ***\n";
        fs.open(file, ios::out); // sola scrittura (riscrive)
    }
    
    
    // file aperto correttamente e senza flag di errori
    if(fs.is_open() && fs.good()) {
        do {
            count++;
            fs << c->id << sep 
            << c->nome << sep
            << c->cognome << sep
            << c->numero << sep
            << c->numero2 << sep
            << c->indirizzo << sep
            << c->citta << sep
            << c->societa << sep
            << c->email << sep;
            // se è l'ultimo contatto non inserisco la newline (problemi in stampa)
            // >> e salvo la posizione (per riprendere la scrittura)
            if(c->next!=nullptr) {
                fs << endl;                              
            }
            else {
                // Suggerimento: nodoSalvato = tail (alla fine è lo stesso)
                nodoSalvato=c;
                nodoSalvato->next=nullptr;
                // Debug: cout << "Nodo salvato: " << nodoSalvato << endl;
            }          

            c=c->next;
        }while(c!=nullptr);

        fs.close();

        // stampo solo se non si tratta di una riscrittura di sistema
        if(rewrite==0)
            cout << "\n*** Salvati " << count << " contatti nel file " << file << " ***" << endl;
        if(rewrite==1 && rubricaSalvata)
            cout << "\n*** File di salvataggio (" << file << ") aggiornato ***" << endl;
        rubricaSalvata=true;
    }
    else {
        cout << "\n*** Impossibile aprire il file: " << file << "\n";
        cout << "Assicurarsi che sia presente nella posizione specificata...\n";
        ret=false;
    } 

    return ret;
}


// Sotto Menu Rubrica - 4 Cancella tutta la Rubrica
Contatto * cancellaRubrica(Contatto *head, Contatto *tail,char filename[],int override=0) {
    //cout << "\nhead (init CANC): " << head << endl;
    //cout << "tail (init CANC): " << tail << endl;

    cleanBuffer();
    int canc=0, cancfile=0; // conferma cancellazione rubrica / file (se salvato)
    Contatto *scorri=head;

    // Chiede se cancellare la rubrica a meno che override non sia impostato a 1 ( => per cancellazione 
    // automatica avviata dal programma)
    if(override==0) {
        cout << "\nSicuro di voler cancellare l'intera rubrica?\n1) SI\n2) NO\n";
        canc=inserNumero(nullptr,1,2);

        if(rubricaSalvata && canc==1) {
            cout << "\nDesideri anche cancellare il file in cui hai salvato la rubrica?\n1) SI\n2) NO\n";
            cancfile=inserNumero(nullptr,1,2);
        }
        
    }
    
    // cancella (canc=responso utente | override=richiesta dal programma)
    if(canc == 1 || override == 1) {
        while(scorri!=nullptr) {
            Contatto *temp = scorri->next;
            delete scorri;
            scorri=temp;              
        }
        
        nodoSalvato=nullptr;

        // cancello anche il file ()
        if(cancfile==1) {
            if(remove(filename)==0)
                cout << "\n*** File " << filename << " cancellato con successo! ***\n ";
            else
                cout << "\n*** Impossibile cancellare il file! ***\n ";
        }

        return scorri;
    }
    else {
        cout << "\nSono contento tu ci abbia ripensato...\n";
        return tail;
    } 
    
}