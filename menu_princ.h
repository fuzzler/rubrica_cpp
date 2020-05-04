//#include "commons.h"
//#include "funz_rubrica.h"


// =====================================================================================================
// FUNZIONI DI MENU PRINCIPALE  ========================================================================
// =====================================================================================================


// ------------------------------------------------------------------------------------------------------
// 0 Main Menu ------------------------------------------------------------------------------------------

// Main Menu - versione 2 
void mainMenu_v2(Rubrica * rubrica) {
    cout << "\n*******************" << endl;
    cout << "| Menu Principale |" << endl;
    cout << "*******************\n" << endl;
    cout << "1) INSERISCI un NUOVO contatto in rubrica" << endl;
    cout << "2) IMPORTA la RUBRICA da file (.csv)" << endl;
    cout << "3) RIEMPI la RUBRICA di contatti casuali (per fare delle prove)" << endl;
    if(rubrica->nContatti>0) {
        cout << "4) OPERAZIONI SUL CONTATTO" << endl;
        cout << "\t- Cerca ( -> Stampa) contatto" << endl;
        cout << "\t- Modifica contatto" << endl;
        cout << "\t- Elimina contatto" << endl;
    }
    if(rubrica->nContatti>1) {
        cout << "5) OPERAZIONI SULLA RUBRICA" << endl;
        cout << "\t- Stampa rubrica" << endl;
        cout << "\t- Ordina la rubrica (NON DISP.)" << endl;
        cout << "\t- Salva rubrica su file" << endl; 
        cout << "\t- Cancella tutta la rubrica" << endl; 
    }
    cout << "6) ESCI " << endl;
}


// MENU 1 Inserisci in Rubrica nuovo Contatto
void inserisciContatto(Rubrica *rubrica, Contatto *nuovo) {
    
    // DEBUG:
    //cout << "Rubrica (in INS): " << rubrica << endl;
    //cout << "Head (in INS): " << rubrica->head <<endl;
    //cout << "Nuovo (in INS): " << nuovo <<endl;

    if(rubrica->head==nullptr) {
        // Inserimento in testa
        nuovo->next=nullptr;
        rubrica->head=nuovo;
        rubrica->tail=nuovo; // per il momento coda e testa coincidono (è un primo inserimento)        
        // manca: rubrica->tail->next=nullptr; // anfrà messo?
    }
    else {
        // Inserimento in coda
        Contatto *cc = rubrica->head; // inizializzo un "CercaCoda" partendo dalla testa

        // sostituire con inserimento diretto in coda (simile a quello in testa)
        while(cc->next!=nullptr) {
            cc=cc->next; // scorro la lista (superfluo...potrei usare la coda)
        }
        cc->next=nuovo; // inserito in coda
        nuovo->next = nullptr;
        rubrica->tail=nuovo; // salvo la coda                
        //DEBUG: cout << "TAIL (INS): " << rubrica->tail << endl;
    }  
    rubrica->nContatti++; // Incremento il numero di contatti 
}


// MENU 2 - Importa la rubrica da file
bool importaRubrica(Rubrica *rub, string file,int ii=0) {
    bool ret=true;
    int count = 0;
    stringstream ss; // stream che conterrà la riga prelevata
    string riga; // riga relevata dal file
    string dati[9];
    
    fstream fs;
    fs.open(file, ios::in);
    // verifica che il file esista (se non esiste -> return false)
    if(fs.is_open() && fs.good()) {
        do {
            count++;            
            idr1++; // cosi successivi contatti saranno sincronizzati
            Contatto *n = new Contatto;

            getline(fs,riga); // prelevo la riga
            ss << riga; // string stream che contiene la riga

            // divido il contenuto della riga
            for(int i=0; i<9; i++)
                getline(ss,dati[i],';'); // metto le porzioni dello stream in un array
            
            // inserisco i dati nell'array dentro
            n->id = dati[0];
            n->nome = dati[1];
            n->cognome = dati[2];
            n->numero = dati[3];
            n->numero2 = dati[4];
            n->indirizzo = dati[5];
            n->citta = dati[6];
            n->societa = dati[7];
            n->email = dati[8];
            

            // Debug: cout << "Riga" << count << " ->  "<<  riga << endl;

            inserisciContatto(rub,n);
        }
        while(!fs.eof());
        fs.close();
        cout << "\n*** Importati " << count << " contatti in Rubrica" << rub->numRubrica << " ***" << endl;
        // Debug: cout << "Ultimo ID: " << dati[0] << endl;

        // Aggiornamento numero ID globale (idr1)
        string portion = dati[0].substr(3); // estrago la porzione contenente il numero dell'id
        int nid = stoi(portion); // converto la stringa col numero in intero -> x il nuovo id
        idr1=nid+1; // nuova posizione salvata per successivi contatti

        // Debug: cout << "Nuovo ID globale: " << idr1 << endl;

    }
    else {
        // se ii (ovvero importazione iniziale) è 0 (importazione comandata dall'utente) stampa il messaggio di errore, se è 1 non serve)
        if(ii==0)
            cout << "\n*** File non aperto: verifica che " << file << " esista e sia leggibile!\n";
        ret=false;
    }
    // estrae i dati da file e li mette in un array (se vuoto-> return false)
    // cicla l'array e inserisce i dati in rubrica
    return ret;
}


// MENU 3 Popola automaticamente la rubrica di dati (per debug e prove)
void popolaRubrica(Rubrica *rubrica, int ni=10) {
    //cout << "Rubrica (popola): " << rubrica << endl;

    string nome, cognome; // verranno scelti casualmente (e usati per generare le email)
    // Archivi dati fittizzi
    string nomi[20] = {"Marco","Giorgio","Beppe","Gina","Alfredo","Valentino","Mirko","Anita","Antonino","Leo",
                        "Luciana","Roberto","Fabrizio","Filippo","Valeria","Alex","Andrea","Anacleto","Teo","Matteo"};
    string cognomi[20] = {"Rossi","Bianchi","Verdi","Tonin","Attanasio","Armando","Moi","Bepi","Vivaldi","Gay",
                        "Negro","Marocco","Franchi","De Michelis","Ugo","Alberta","Marin","Romano","Tetti","Mattea"};
    string domini[10] = {"@libero.it","@yahoo.it","@info.it","@enterprise.it","@microcom.it","@zipper.it",
                        "@f-society.it","@arianna.it","@hotmail.com","@lycos.it"};
    string indirizzi[20] = {    "Strada delle Cacce","Via delle Begonie","Via Vado",
                                "Via Ormea","Via Saluzzo",
                                "Corso Stati Uniti","Corso Brescia","Via Torino",
                                "Piazza Martiri","Via Lemani",
                                "Strada Revigliasco","Via Franchini","Via Petitti", 
                                "Via Nizza", "Via Madama Cristina",
                                "Viale Roma","Piazza Onorati","Largo Orbassano",
                                "Via Tetti di Rivoli","Via Vioux"};
    string citta[20] = {"Roma","Bergamo","Vicenza","Torino","Ancona","Asti","Milano","Belluno","Verona","Genova",
                        "Napoli","Mantova","Firenze","Domodossola","Udine","Alessandria","Modena",
                        "Rieti","Trapani","Forlimpopoli"};
    string societa[20] = {"Itoa","Dylog","CSI","NovaNext","Art","Software","Bit Bit","Overflow",
                        "Lochiva","SIE","Domini Val","Super Flash","SW Solution","Blueprint",
                        "ArpaNet","Blackout","TopIX","SkyLab","VirtualBit","Future"};
    string tiposoc[20] = {"s.r.l.","S.p.A.","Inc.","Corp.","S.S.","S.a.S.","s.r.l."
                            ,"S.p.A.","Inc.","Corp.","S.S.","S.a.S.", "Ass.","Soc Coop",
                            "s.r.l.","S.p.A.","Inc.","Corp.","S.S.","S.a.S."};

    srand(time(0));

    // Ciclo per ni (numero inserimenti) passato
    for(int i=0; i<ni; i++) {
        // nuovo contatto da popolare
        Contatto *nuovo = new Contatto;
        
        int randnum = rand()%20;
        nome=nomi[rand()%20];
        cognome=cognomi[rand()%20];

        // DEBUG: controllo che non si sfori
        if(randnum>19) {
            cout << "\nWARNING - ARRAY OFFSET! (" << randnum << ")" << endl;
        }

        nuovo->id='R'+to_string(rubrica->numRubrica)+'-'+to_string(idr1);
        nuovo->nome=nome;
        nuovo->cognome=cognome;
        nuovo->numero="0"+to_string(rand()%999)+"-"+to_string(rand()%9999999);
        nuovo->numero2=to_string(rand()%(351-310)+310)+"/"+to_string(rand()%9999999);
        nuovo->indirizzo=indirizzi[rand()%20]+", "+to_string(rand()%359);
        nuovo->citta=citta[rand()%20];
        nuovo->societa=societa[rand()%20]+" "+tiposoc[rand()%20];
        nome[0] = tolower(nome[0]); // iniziali minuscole
        cognome[0] = tolower(cognome[0]);
        nuovo->email=nome+"."+cognome+domini[rand()%10];
        idr1++; // incremento contatore id per rubrica 1 (static global)
        
        inserisciContatto(rubrica,nuovo);
    }
} // fine popolaRubrica