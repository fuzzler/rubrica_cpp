//#include "commons.h"
//#include "funz_rubrica.h"


// =====================================================================================================
// FUNZIONI DI SOTTOMENU 4 - Operazioni su Contatto  ===================================================
// =====================================================================================================

// Sottomenu 4 - 0 menu contatto
void menuContatto() {
    cout << "\nMenu Contatto";
    cout << "\n*************\n\n";
    cout << "1) CERCA (STAMPA) contatto" << endl;
    cout << "2) MODIFICA contatto" << endl;
    cout << "3) ELIMINA contatto" << endl;
    cout << "4) Torna al menu principale" << endl;
}


// Sottomenu 4 - 1 Cerca contatto (tail è facoltativo e scelta potrebbe essere passato in auto)
Contatto *cercaContatto(Contatto *head, Contatto *tail=nullptr, int scelta=0) {

    // DEBUG: 
    //Controllare head e soprattutto tail -> bad_alloc su ricerca ultimo contatto(3)
    //Verificare anche le altre scelte del menu

    cleanBuffer(); // azzero il buffer (per sicurezza)

    //int scelta=0; // scelta utente menu
    bool trovato=false;
    string id,nome,cognome,telefono; // id,nome,cognome,telefono da cercare
    Contatto *src = head; // per le ricerche

    if(scelta==0) {
        cout << "\nQuale contatto cerchi? " << endl;
        cout << "**********************\n\n";
        // MENU
        cout << "1) Il primo della lista" <<  endl;
        cout << "2) L'ultimo della lista" << endl;
        cout << "3) L'ultimo inserito" << endl;
        cout << "4) Cercalo tramite ID" << endl;
        cout << "5) Cercalo in base al nome e al cognome" << endl; // non prevede ancora i casi di omonimia
        cout << "6) Cercalo in base al primo numero di telefono" << endl;
        cout << "7) Torna indietro" << endl;

        scelta=inserNumero(nullptr,1,7);
    }
    
    switch(scelta) {

        case 1:
            // stampa il primo della lista (head)
            //stampaContatto(head);
            src = head;
            trovato=true;
        break;

        case 2:
            // stampa l'ultimo della lista (tail)
            //stampaContatto(tail);
            src = tail;
            trovato=true;
        break;

        case 3:
            // stampa l'ultimo inserito -> va cercato il nodo con il numero idr1 maggiore
            while(src!=nullptr) {
                // converto in intero con stoi la porzione di id estratta con substr 
                // (che corrisponde a idr1 assegnato) con idr1 attuale -1 (c'è stato l'incremento)
                int idn = stoi((src->id).substr(3));
                //cout << "Numero ID: " << idn << endl;
                if(idn==(idr1-1)) {
                    //stampaContatto(src);
                    savedTemp=src; // salvo l'indirizzo trovato a livello globale (è una prova)
                    trovato=true;
                    break;
                }
                src=src->next;
            }
            
        break;

        case 4:
            // ricerca per id
            cout << "Inserisci l'ID da cercare in rubrica (es R1-12) " << endl;
            cout << "Attenzione! Rispetta le maiuscole e non tralasciare il simbolo - " << endl;
            cin >> id;

            while(src!=nullptr) {
                // converto in intero con stoi la porzione di id estratta con substr 
                // (che corrisponde a idr1 assegnato) con idr1 attuale -1 (c'è stato l'incremento)
                if(src->id==id) {
                    //stampaContatto(src);
                    //savedTemp=src; // salvo l'indirizzo trovato a livello globale
                    trovato=true;
                    break;
                }
                src=src->next;
            }
        break;

        case 5:
            // ricerca per nome e cognome
            cleanBuffer(1);
            cout << "Inserisci il nome (rispettando le maiuscole): ";
            getline(cin,nome);

            cleanBuffer();
            cout << "Inserisci il cognome (rispettando le maiuscole ed eventuali spazi): ";
            getline(cin,cognome);

            while(src!=nullptr) {
                // converto in intero con stoi la porzione di id estratta con substr 
                // (che corrisponde a idr1 assegnato) con idr1 attuale -1 (c'è stato l'incremento)
                if(src->nome==nome && src->cognome==cognome) {
                    //stampaContatto(src);
                    //savedTemp=src; // salvo l'indirizzo trovato a livello globale
                    trovato=true;
                    break;
                }
                src=src->next;
            }
        break;

        case 6:
            // ricerca per telefono
            cleanBuffer(1);
            cout << "Inserisci il numero (rispettando le maiuscole ed eventuali spazi o simboli): ";
            getline(cin,telefono);

            while(src!=nullptr) {
                // converto in intero con stoi la porzione di id estratta con substr 
                // (che corrisponde a idr1 assegnato) con idr1 attuale -1 (c'è stato l'incremento)
                if(src->numero==telefono) {
                    //stampaContatto(src);
                    //savedTemp=src; // salvo l'indirizzo trovato a livello globale
                    trovato=true;
                    break;
                }
                src=src->next;
            }
        break;

        case 7:
            // non fa niente e spreca lo switch uscendo
            src=nullptr; // altrimenti ritorna la testa (head) senza che sia richiesto
        break;

        default:
            cout << "Input inserito non valido!!"<< endl;
            cleanBuffer();
            scelta=0;
        break;

        // responso negativo della ricerca
        
    } // fine switch

    if(!trovato)
        cout <<"\n *** Nessun contatto trovato con i parametri utilizzati! ***" << endl;

    return src;
} // fine cerca contatto


// Sottomenu 4 - 2 Modifica elemento in rubrica (Ricerca) 
bool modificaContatto(Contatto *head,Contatto *tail) {

    cleanBuffer();
    int cid=0,scelta=0,continua=0; // cid: per valutare se l'utente conosce l'id / scelta: quale campo cambiare / continua: continui? 1=si
    bool stay=true,ret=false;
    string input=""; // input dell'utente
    Contatto *scorri = head,*damod=nullptr; // scorri -> cerca / damod -> quello da modificare
    /*
    DEBUG:
    cout << "\nInserisci L'ID del Contatto che vuoi modificare (es. R1-15) " << endl;
    cout << "Se non ricordi l'ID puoi cercarlo digitando il \"cerca\". " << endl;
    cout << "Se vuoi modificare l'ultimo contatto inserito digita \"ultimo\". " << endl;
    cout << "Se preferisci tornare al menu digita \"menu\". " << endl;
    */

    cout << "Conosci l'ID del contatto da modificare?\n1) SI\n2) NO\n";
    cid=inserNumero(nullptr,1,2);

    cleanBuffer(); // ripulisco per sicurezza

    if(cid==1) {
        cout << "\nInserisci L'ID del Contatto che vuoi modificare (es. R1-15) " << endl;
        cin >> input;

        while(scorri->next!=nullptr) {
            
            if(scorri->id==input) {
                //cout << "*Scorri (Modifica): " << scorri << endl;
                damod=scorri;
                break;
            }            
            scorri=scorri->next;
        }
    }

    if(cid==2) {
        damod=cercaContatto(head,tail,0);
    }

    // inizia la vera operazione
    if(damod==nullptr) {
        cout << "\n***\nContatto NON trovato!\nAssicurati che sia inserito in rubrica...\n***\n";
    }
    else {
        
        do {
            cout << "\nVerrà modificato il seguente contatto:";
            cout << "\n**************************************\n\n";
            stampaContatto(damod);
            cout << "\nQuale campo di "<<damod->id<<" vuoi cambiare?" << endl;
            cout << "******************************************\n\n";
            cout << "1) Nome" << endl;
            cout << "2) Cognome" << endl;
            cout << "3) Numero 1" << endl;
            cout << "4) Numero 2" << endl;
            cout << "5) Indirizzo" << endl;
            cout << "6) Citta" << endl;
            cout << "7) Societa" << endl;
            cout << "8) E-mail" << endl;

            cleanBuffer(); // ripulisco per sicurezza
            scelta=inserNumero(nullptr,1,8);
            fflush(stdin);

            cleanBuffer(1); // ripulisco per sicurezza
            switch(scelta) {
                case 1:
                    damod->nome=inserStringa("nome");
                break;

                case 2:
                    damod->cognome=inserStringa("cognome");
                break;

                case 3:
                    damod->numero=inserStringa("numero 1");
                break;

                case 4:
                    damod->numero2=inserStringa("numero 2");
                break;

                case 5:
                    damod->indirizzo=inserStringa("indirizzo");
                break;

                case 6:
                    damod->citta=inserStringa("citta");
                break;

                case 7:
                    damod->societa=inserStringa("societa");
                break;

                case 8:
                    damod->email=inserStringa("email");
                break;
            }

            cout << "\nDesideri cambiare altri campi?\n1) SI\n2) NO\n";
            continua=inserNumero(nullptr,1,2);

            if(continua==2) {
                stay=false;
            }
        } while(stay);
        
        cout << "\nStampa delle modifiche riportate:";
        cout << "\n*********************************\n";
        stampaContatto(damod);
        ret = true;
    } // fine else (contatto trovato?)

    return ret;   
}


// Sottomenu 4 - 3 Cancella elemento in rubrica (Ricerca)
bool cancellaContatto(Rubrica *rub) {

    cleanBuffer();
    bool ret=false;
    int cid=0,confcanc=0; // cid -> l'utente conosce l'id? / confcanc = conferma cancellazione
    string input=""; // input dell'utente
    Contatto *scorri = rub->head,*dacanc=nullptr,*prec=nullptr; // scorri->cerca / dacanc->quello da cancellare / prec->elemento precedente)

    cout << "\nFunzione di cancellazione del contatto scelto tramite ID" << endl;
    cout << "********************************************************\n\n";

    cout << "Conosci l'ID del contatto da cancellare?\n1) SI\n2) NO\n";
    cid=inserNumero(nullptr,1,2);

    cleanBuffer(); // ripulisco per sicurezza

    if(cid==1) {
        cout << "\nInserisci L'ID del Contatto che vuoi cancellare (es. R1-15) " << endl;
        cin >> input; 
        while(scorri->next!=nullptr) {
            
            if(scorri->id==input) {
                //cout << "*Scorri (Modifica): " << scorri << endl;
                dacanc=scorri;
                break;
            }            
            scorri=scorri->next;
        }      
    }

    if(cid==2) {
        dacanc=cercaContatto(scorri,rub->tail,0);
        if(dacanc!=nullptr) 
            input=dacanc->id;
    }

    // Richiedo conferma
    if(dacanc!=nullptr) {
        cout << "\nVerrà cancellato il seguente contatto: " << endl;
        stampaContatto(dacanc);
        cout << "\nConfermi?\n1) SI\n2) NO\n";
        confcanc=inserNumero(nullptr,1,2);
    }
    else {
        cout << "\n*** Contatto NON trovato! ***\n";
        cout << "Assicurati di aver scritto correttamente l'ID o che sia presente in rubrica.\n";
    }

    // resetto scorri
    scorri=rub->head;

    if(confcanc==1) {
        while(scorri!=nullptr) {

            if(scorri->id==dacanc->id) {   
                if(scorri==rub->head) {
                    // se devo cancellare il primo -> testa punta al secondo
                    //cout << "\nCancello " << scorri->id << endl;
                    rub->head = scorri->next;
                }
                else if(scorri==rub->tail) {
                    rub->tail = prec;
                    rub->tail->next = nullptr;
                }
                else {
                    // DEBUG:
                    /*
                    cout << "\nPrec: " << prec->id << endl;
                    cout << "Prec-next ID: " << prec->next->id << endl;
                    cout << "Scorri-next ID: " << scorri->next->id << endl;
                    */
                    prec->next = scorri->next;
                } 

                cout << "\nCancellato Contatto " << scorri->id << endl;
                delete scorri;
                rub->nContatti--; // diminuisco il numero di contatti totali
                ret=true;
                break;
            }
            prec=scorri;
            scorri=scorri->next;
        }// fine while
    }

    return ret;
}