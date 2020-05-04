//#include "commons.h"

// ********************************************************************************************************
// FUNZIONI USATE DAL PROGRAMMA ***************************************************************************
// ********************************************************************************************************


// Resetta il buffer
void cleanBuffer(int param=0) {
    fflush(stdin);
    cin.clear();
    if(param==1) 
        cin.ignore(1000,'\n');
}


// Controlla i numeri interi inseriti (ritorna false se l'input va bene, true se l'input è invalido)
bool ctrlInput(int input, Rubrica *rubrica1=nullptr) {

    bool ret = true;

    if(cin.fail() || cin.gcount()>1) {
        cleanBuffer(1);
        cout << "SCELTA NON VALIDA!\n\nPremere un tasto per continuare...\n";
    }
    // Se in rubrica non c'è ancora nessun elemento le opzioni tra 2 e 7 sono disabilitate
    else if(rubrica1 != nullptr && rubrica1->nContatti<1 && input==4) {
        cout << "Non puoi ancora selezionare questa opzione: (4=Operazioni su Contatto)" << endl;
        cout << "Deve essere presente almeno 1 contatto in rubrica." << endl;
        cout << "Premi 0 per tornare al Menu."<<endl;
    }
    // Se in rubrica non ci sono almeno 2 elementi le opzioni tra 5 e 7 sono disabilitate
    else if(rubrica1 != nullptr && rubrica1->nContatti<2 && input==5) {
        cout << "Non puoi ancora selezionare questa opzione: (5=Operazioni su Rubrica)" << endl;
        cout <<"Devono essere presenti almeno 2 contatti in rubrica." << endl;
        cout <<"Premi 0 per tornare al Menu." << endl;
    }
    else {
        ret=false;
    }
    return ret;
}

// Controllo inserimento dello Username
bool ctrlUsername(string username) {

    bool ret=true;
    int lettera;
    for(int i=0; i<username.length(); i++) {
        lettera = username[i];
        //cout << username[i] << " -> "<< lettera << endl; // debug
        // Range ammessi: 65 - 90 | 97-122 (minusc)
        if((lettera < 97 && lettera > 90) || lettera > 122 || lettera < 65) {
            ret=false;
            break;
        }
    }

    return ret;
}


// Inserisce il nome
string inserStringa(string tipo) {
    cout << "\nInserisci " << tipo << ":\n";
    //cleanBuffer(1); // col passaggio di 1 si attiva cin.ignore
    string dato;
    getline(cin,dato);
    return dato;
}

// inserimento di un numero (qualsiasi)
int inserNumero(Rubrica *rub, int min, int max) {
    //cleanBuffer();
    int num;
    cin >> num;
    fflush(stdin);
    while(ctrlInput(num, rub) ||(num < min && num > max)) {
        cleanBuffer(1);
        num=0;
        cout << "\nScegli un opzione tra " << min << " e " << max << "\n";
        cin >> num;
        fflush(stdin);
    }
    return num;
}

// inserisce un dato di tipo stringa, la sola differenza è che chiede all'utente se inserirlo
string insDato(string tipo) {
    int inser=0;
    string dato;

    cout << "Desideri inserire "<< tipo <<"?\n1 - Si\n2 - No\n";
    inser=inserNumero(nullptr,1,2);

    cleanBuffer(1); // + cin.ignore
    if(inser == 1) {
        //cout << "Inserisci " << tipo << endl;
        dato=inserStringa(tipo);
    }
    else {
        dato="";
    }
    return dato;
}


// Crea un nuovo contatto -> ritorna un puntatore (funzione nativa della struct Contatto) **** ORIGINAL ****
Contatto * creaContatto(int nr) { // viene passato il numero rubrica
    //cout << "Nuovo (in creaContatto): " << &nuovo << endl;
    string id='R'+to_string(nr)+'-'+to_string(idr1);
    string nome, cognome, numero, numero2,indirizzo, citta, societa, email;
    int inser;
    idr1++; // incremento il valore globale

    cout << "\nCreazione del Nuovo Contatto:"; 
    cout << "\n*****************************\n\n";

    cout << "ID impostato: " << id << endl;

    cleanBuffer(1); // col passaggio di 1 si attiva cin.ignore
    nome=inserStringa("nome");
    
    cleanBuffer();
    cognome=inserStringa("cognome");

    cleanBuffer();
    numero=inserStringa("primo numero telefonico"); 

    cleanBuffer();
    numero2=insDato("secondo numero"); 

    cleanBuffer();
    indirizzo=insDato("indirizzo"); 

    cleanBuffer();
    if(indirizzo !="") {
        citta=inserStringa("citta'"); 
    }    

    cleanBuffer();
    societa=insDato("una societa'"); 

    cleanBuffer();
    email=insDato("un'email");


    Contatto *nuovo = new Contatto {id,nome,cognome,numero,numero2,indirizzo,citta,societa,email};
    return nuovo; 
}


// (NON USATO) Overload con passaggio parametri nuovo e nrub (numero rubrica) + nc (1=è un nuovo contatto)
void creaContatto(Contatto *nuovo, int nrub=0, int nc=0) {

    int ins_email=0; // responso utente alla domanda di inserimento email
    string id;
    
    
    // Se nc = 1 allora si tratta di un nuovo inserimento
    if(nc == 1) {
        // creazione ID Rubrica  
        //stringstream ssid; ssid << 'R' << nrub << '-' << idr1; id=ssid.str();
        id = 'R'+to_string(nrub)+'-'+to_string(idr1);

        // Assegnazione ID rubrica
        nuovo->id=id;
        idr1++; // Incremento globale idr1

        cout << "\nCreazione del Nuovo Contatto:"; 
        cout << "\n*****************************\n";
        cout << "\nImpostato ID a " << nuovo->id;
        //cout << " (Risultato di Nrub: " << nrub << " e IDR1: " << idr1;
    }
    

    //cleanBuffer(1); // col passaggio di 1 si attiva cin.ignore
    cout << "\nInserisci nome\n";
    //getline(cin,nuovo->nome);
    nuovo->nome=inserStringa("nome");
    cout << "Nome inserito: " << nuovo->nome << endl;
    
    cleanBuffer();
    cout << "Inserisci cognome\n";
    getline(cin,nuovo->cognome);
    

    cleanBuffer();
    cout << "Inserisci il numero telefonico\n";
    cin >> nuovo->numero; 

    //cleanBuffer();
    cout << "Desideri inserire una e-mail?\n1 - Si\n2 - No\n";
    ins_email=inserNumero(nullptr,1,2);

    cleanBuffer(1);
    if(ins_email == 1) {
        cout << "Inserisci e-mail\n";
        getline(cin, nuovo->email);
    }
    else {
        nuovo->email="";
    }
} // fine crea contatto


// stampa il contatto di cui è passato il puntatore (e un numero che stabilisce se è chiamata da stampaRubrica -> stampe in serie)
void stampaContatto(Contatto *elem,int serie=0) {
    cout << "\n+-----------------------------------------------+\n\n";
    cout << "ID:\t\t" << elem->id << endl;
    cout << "Nome:\t\t" << elem->nome << endl;
    cout << "Cognome:\t" << elem->cognome << endl;
    cout << "Numero:\t\t" << elem->numero << endl;
    if(elem->numero2!="") {
        cout << "Numero 2:\t" << elem->numero2 << endl;
    }
    if(elem->indirizzo!="") {
        cout << "Indirizzo:\t" << elem->indirizzo << endl;
        cout << "Citta':\t\t" << elem->citta << endl;
    }
    if(elem->societa!="") {
        cout << "Societa:\t" << elem->societa << endl;
    }
    if(elem->email!="")
        cout << "Email:\t\t" << elem->email << endl;

    if(serie==0)
        cout << "\n+-----------------------------------------------+\n";
}