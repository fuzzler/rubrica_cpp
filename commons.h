/**
 * Questo libreria contiene:
 *  - le inclusioni a librerie esterne native del linguaggio utili al programma (ed alle altre sue librerie).
 *  - le variabili globali
 *  - le strutture dati (structs)
 */

#include <iostream>
#include <cstdio>
#include <cstring> // per usare memcpy()
#include <string>  // per usare stoi
#include <cstdlib> // per usare malloc calloc free
#include <iomanip> // per formattare con setfill e setw
#include <ctime> // per estrazioni casuali
#include <cctype> // per usare tolower / toupper
#include <fstream> // per operazioni su file -> importare / esportare rubrica 


using namespace std; // sconsigliato in generale (usato per comodità-> tolto per usare std di cctype)
//using std::cout, std::string, std::cin, std::endl, std::stringstream, std::to_string;
//using std::tolower;

// Indirizzo come struttura -> per ora non ancora utilizzato -> nella successiva versione
struct Indirizzo {
    string indirizzo;
    string citta;
};

struct Contatto {
    string id;
    string nome;
    string cognome;
    string numero;
        
    string numero2;
    string indirizzo;
    string citta;
    string societa;    
    
    string email;
    Contatto *next;
};


struct Rubrica {
    int numRubrica; // numero rubrica (nel caso ce ne fosse piu di una)
    string nomeRubrica;
    int nContatti; // numero contatti
    char ordine; // ordina rubrica per N=nome, C=Cognome ...
    Contatto *head,*tail;
};


// VARIABILI GLOBALI
bool rubricaSalvata=false; // certifica che esiste il file in cui è stata salvata la rubrica per utente
static int idr1 = 1; // ID della Rubrica 1 (in futuro potrebbero esserci più rubriche)
static int numeroRubrica = 1; // numero della Rubrica creata (nel caso vengano create piu rubriche)
Contatto *nodoSalvato = nullptr; // in caso di multipli salvataggi su file riparte da questo punto (non riscrive ogni volta il file)
Contatto *savedTemp; // contatto temporanealmente salvato con scope globale (non utilizzato)



// PROTOTIPI delle Funzioni
Contatto *cercaContatto(Contatto *h,Contatto *t,int n); // perche completato dopo la sua chiamata
void creaRubrica(); // Crea rubrica (prototipo) -> nel caso si vogliano creare più rubriche (prossima versione)

// Funzioni generiche
//int inserNumero(Rubrica *rub, int min, int max);
