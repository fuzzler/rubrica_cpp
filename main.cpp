/**
 * Programma che permette il salvataggio digitale di contatti personali.
 * Si consiglia di consultare la documentazione allegata (README.md o README.txt) per ulteriori
 * informazioni circa il suo funzionamento
 * 
 * Librerie (custom)
 * - commons.h -> contiene tutte le librerie native, variabili globali, e strutture dati necessarie all'intero progetto
 * - funz_rubrica.h -> contiene una suite di funzioni usate dai vari menu del programma
 * - menu principale -> contiene il menu principale e le funzioni ad esso correlate
 * - menu4 -> contiene le funzioni del sotto menu 4 (ovvero operazioni sul Contatto)
 * - menu5 -> contiene le funzioni del sotto menu 5 (ovvero operazioni sulla Rubrica)
 */


#include "commons.h"
#include "funz_rubrica.h"
#include "menu_princ.h"
#include "menu4.h"
#include "menu5.h"


// *********************************************************************************************
// ** MAIN *************************************************************************************
// *********************************************************************************************

int main() {

    // Variabili del Main
    // Inizializzazione di una rubrica  NOME    N Contatti  Ordine  *Head   *Tail
    Rubrica *rubrica1 = new Rubrica {1,"Rubrica personale",0,' ',nullptr,nullptr};
    Contatto *nuovo=new Contatto,*temp; // nuovo = Contatto da popolare / temp = puntatore temporaneo
	bool stay=true,stayin=true; // stay | stayin = rimani nel ciclo (stayin -> ciclo interno)
    bool salvataggio=false,import=false; // esito del salcataggio su file / import=responso sull'importazione della rubrica
    bool confcanc = false,confmod=false; // conferma cancellazione contatto /modifica contatto
    int nrub=rubrica1->numRubrica;
    int option = 0, optionin = 0; // scelte del menu -> (0 = Main Menu)
    int popola = 0; // popola la rubrica di tot numeri
    string importFile,username; // nome del file da cui importare (chiesto all'utente) / file in cui è salvata la rubrica / username=nome utente
    

	// PROGRAM START - WELCOME MESSAGE *************************************
	cout << "\no====================================================o" << endl;
	cout << "| Benvenuti nel Programma RUBRICA TELEFONICA  v1.1.0 |" << endl;
	cout << "o====================================================o\n" << endl;

    cout << "Inserisci il tuo nome:\n(Niente numeri o caratteri speciali)" << endl;
    cin >> username;

    while(!ctrlUsername(username)) {
        cout << "\n*** Username inserito NON valido! ***\n";
        cout << "Sono ammesse solo lettere dalla A alla Z (anche minuscole)\n";
        cleanBuffer();
        cin >> username;
    }

    cout << "\nBenvenuto " << username << " nella tua rubrica appena creata per te!\n\n";

    // imposto un nome file dopo aver scelto uno username (e creato una rubrica)
    string nomefile="Rubrica"+to_string(nrub)+'_'+username+".csv";
    char nomefile_char[nomefile.size()+1];
    strcpy(nomefile_char, nomefile.c_str());// conversione di nomefile in array di char (per funzione remove->cancellaRubrica)
    // caricare il file rubrica in base al nome utente
    import=importaRubrica(rubrica1,nomefile,1);
    if(import) {
        cout << "\n*** File importato: " << nomefile << " ***\n";
        rubricaSalvata=true;
    }
    else {
        cout << "\n*** Nessun file presente nel percorso locale da cui importare la rubrica. *** \n";
    }

	// PROGRAMMA PRINCIPALE: esegue operazioni finche l'utente non decide di uscire
	while(stay) {

        switch (option) {

            case -1:
                cout << "\nAdesso cosa vuoi fare " << username << "?"<< endl;
                option=0;
            break;

            case 0:
                // Inserire controllo se esiste una rubrica creata
                mainMenu_v2(rubrica1);
                option=inserNumero(rubrica1,1,6);
            break;

            case 1:
                // CREAZIONE E INSERIMENTO DI UN NUOVO CONTATTO

                // DEBUG:
                //cout << "\nRubrica: " << rubrica1 <<endl;
                //cout << "Head (prima di ins): " << rubrica1->head <<endl;
                //cout << "Nuovo (prima di creaz): " << nuovo <<endl;

                nuovo = creaContatto(nrub); // chiama la funzione che restituisce un contatto
                inserisciContatto(rubrica1,nuovo); // rubrica passaggio per valore
                option=-1;
            break;

            case 2:
                // IMPORTA RUBRICA DA FILE
                cleanBuffer();
                cout << "\nInserisci il percorso e il NOME del FILE da cui importare la rubrica\n";
                cout << "Se il FILE è nella stessa cartella del programma è sufficiente il NOME del FILE.\n";
                cin >> importFile;
                import=importaRubrica(rubrica1,importFile);

                if(import) {
                    cout << "\n*** Rubrica importata con successo da " << importFile << " ***\n";
                    rubricaSalvata=true;
                }
                else {
                    cout << "\n*** Nessun nuovo contatto aggiunto! ***\n";
                }
                option=-1;
            break;

            case 3:
                // popola la rubrica con dati di prova
                cout << "\nQuanti contatti vuoi inserire? ";
                cin >> popola;
                popolaRubrica(rubrica1,popola);
                cout << "\nContatti inseriti:";
                cout << "\n******************\n\n";
                stampaRubrica(rubrica1->head);
                option=-1;
            break;

            case 4:
                // OPERAZIONI SUL CONTATTO ------------------------------------------------------------------

                optionin=0; // opzioni dei sottomenu
                stayin=true; // reset condizione

                while(stayin) {
                    switch (optionin) {

                        case 0:
                            menuContatto();
                            optionin=inserNumero(nullptr,1,4);
                        break;

                        case 1:
                            temp=cercaContatto(rubrica1->head,rubrica1->tail);
                            stampaContatto(temp);
                            optionin=0;
                        break;

                        case 2:
                            // MODIFICA CONTATTO
                            confmod=modificaContatto(rubrica1->head, rubrica1->tail);

                            // Sincronizzazione con il file salvato in rubrica
                            //      ( solo se è stato effettivamente cancellato un contatto 
                            //      e se esiste un file in cui è salvata la rubrica)
                            if(rubricaSalvata && confmod) {
                                // se il file viene aperto -> richiamo la scrittura su file con rewrite=1 (riscrive - no append)
                                salvaRubrica(rubrica1,nomefile,1);
                            }
                            optionin=0;
                        break;

                        case 3:
                            // CANCELLA CONTATTO
                            confcanc=cancellaContatto(rubrica1);

                            // Sincronizzazione con il file salvato in rubrica
                            //      ( solo se è stato effettivamente cancellato un contatto 
                            //      e se esiste un file in cui è salvata la rubrica)
                            if(rubricaSalvata && confcanc) {
                                // se il file viene aperto -> richiamo la scrittura su file con rewrite=1 (riscrive - no append)
                                salvaRubrica(rubrica1,nomefile,1);
                            }
                            optionin=0;
                        break;

                        case 4:
                            // Uscita
                            stayin=false; // esce
                            option=-1; // torna al menu principale
                        break;
                    
                        default:
                            cout << "\n*** Scelta inserita non valida! ***\n";
                        break;
                    }
                }
            break;

            case 5:
                // OPERAZIONI SULLA RUBRICA -----------------------------------------------------------------
                optionin=0; // opzioni dei sottomenu
                stayin=true; // reset condizione

                while(stayin) {
                    switch (optionin) {

                        case 0:
                            menuRubrica();
                            optionin=inserNumero(nullptr,1,5);
                        break;

                        case 1:
                            // STAMPA LA RUBRICA
                            if(rubrica1->head!=nullptr) {
                                cout << "\nStampa della Rubrica numero " << rubrica1->numRubrica;
                                cout << " - " << rubrica1->nomeRubrica;
                                cout << " - Numero Contatti: " << rubrica1->nContatti << "\n";
                                cout << "**************************************************************************\n\n";
                                stampaRubrica(rubrica1->head); 
                            }
                            else {
                                cout << "\n*** Nessun Contatto in Rubrica ***\n";
                            }       
                            optionin=0;
                        break;

                        case 2:
                            // ORDINA LA RUBRICA
                            cout << "\n*** Verrà ordinata la rubrica in base al cognome ***" << endl;
                            cout << "\n*** FUNZIONE NON ANCORA DISPONIBILE! ***" << endl;
                            if(rubrica1->head!=nullptr) { 
                                // come ordinare?
                                // cognome ?  societa ? -> non deve essere facoltativo l'inserimento 
                                // per ora ordina solo per cognome                             
                                //ordinaRubrica(rubrica1); 
                            }
                            else {
                                cout << "\n*** Nessun Contatto in Rubrica ***\n";
                            }
                            optionin=0;
                        break;

                        case 3:
                            // SALVA SU FILE
                            cout << "\n*** Salvataggio rubrica in corso... ***\n";
                            if(rubrica1->head!=nullptr)
                                salvataggio=salvaRubrica(rubrica1,nomefile);
                            if(salvataggio) {                                
                                cout << "\nRubrica salvata sul file: " << nomefile << endl;
                            }
                            else {
                                cout << "\nRubrica non salvata!\n";
                            }
                            optionin=0;
                        break;

                        case 4:
                            // CANCELLA TUTTA LA RUBRICA
                            if(rubrica1->head!=nullptr) {
                                rubrica1->tail=cancellaRubrica(rubrica1->head, rubrica1->tail,nomefile_char);
                            }
                            else {
                                cout << "\n*** Nessun Contatto in Rubrica ***\n";
                            }
                            
                            if(rubrica1->tail==nullptr) {
                                cout << "\n*** Rubrica cancellata con successo ***\n";
                                rubrica1->nContatti=0; // azzero il conteggio
                                rubrica1->head = nullptr; // il puntatore di testa punta a un area di memoria vuota -> lo azzero
                                idr1=1; // azzero il conteggio degli ID
                                optionin=5;
                            }
                            else {
                                optionin=0; // se non cancello (ripensamento) rimango nel sottomenu
                            }
                            
                        break;

                        case 5:
                            // Uscita
                            stayin=false; // esce
                            option=-1; // torna al menu principale
                        break;
                    
                        default:
                            cout << "\nScelta inserita non valida!\n";
                        break;
                    }
                }
            break;

            case 6:
                // Uscita dal programma (cancello tutti dati nella memoria HEAP)
                rubrica1->tail=cancellaRubrica(rubrica1->head,rubrica1->tail,nomefile_char,1);
                if(rubrica1->tail==nullptr) 
                    cout << "\n*** Dati salvati in RAM cancellati (memoria liberata) ***\n";
                stay=false;
            break;

            default:
                cout << "Opzione selezionata NON valida!\n";
                option=0;
            break;
        }
		
	} // fine while programma

	cout << "\no========================o\n";
	cout << "| CHIUSURA del PROGRAMMA |\n";
	cout << "o========================o\n\n";

    return 0;
}