DOCUMENTAZIONE DEL PROGRAMMA `RUBRICA TELEFONICA` - FuzzlerNet Productions
==========================================================================
  
### Descrizione del programma e delle funzionalità

Software realizzato a scopo didattico eseguibile da riga di comando.   
Scritto in **`C++`** .  
Fa utilizzo del paradigma procedurale (no `OOP`) e si serve dei seguenti strumenti:  
- Struct
- Linked List
- File stream
- Allocazione dinamica della memoria
  
#### Funzionalità generali

Il software permette di salvare un elenco dei contatti, inizialmente a runtime, ma trasferibili in locale su file con estensione `.csv`. Una volta chiuso il programma la memoria allocata viene cancellata automaticamente ma i contatti (se salvati su file) sono re-importabili e modificabili a runtime.    
Le modifiche eseguite sui contatti generati vengono automaticamente scritti sul file di salvataggio (se presente) il cui nome sarà sempre:   `Rubrica [numero-rubrica] _ [nome-utente] .csv`  

Il software prevede anche che la lista contatti venga messa in ordine (funzione non ancora abilitata).  

Il software prevederà nelle successive versioni la creazione di più rubriche per utente (da cui il motivo di specificare il numero rubrica nel nome del file).  

#### Analisi del funzionamento e del MENU PRINCIPALE

**Username**  
Una volta lanciato il programma da terminale, ci verrà chiesto di inserire uno `username`. E' bene tener presente che questo verrà usato per generare il nome del file, insieme al numero della rubrica creata (per ora come impostazione predefinita viene usata una sola rubrica per utente). Lo `username` può essere composto solo da lettere dell'alfabeto maiuscole o minuscole, non può contenere caratteri speciali o numeri.  
Si consiglia di usare il proprio nome e/o cognome.  

**Importazione automatica**  
Una volta inserito lo `username` e creata la rubrica (per ora fatto in automatico), il programma andrà a cercare nella cartella in cui risiede un file di salvataggio che contenga nel nome lo username inserito. Se lo trova importerà automaticamente i contatti in memoria centrale per effettuare le operazioni più velocemente.
  
**Menu**   
Una volta scelto uno `username` verrà mostrato il menu principale: se è la prima volta che aprimo il programma o non abbiamo salvato i contatti in un file locale (cioè nella stessa cartella in cui risiede il programma stesso) allora le scelte saranno 4:  
- 1) Inserisci nuovo contatto
- 2) Importa rubrica da file
- 3) Crea contatti random (per fare delle prove)
- 6) Esci
  
Le voci 4) e 5) compariranno appena avremmo inserito uno (4) o più (5) contatti.  
1) I contatti vengono salvati in una `Lista Concatenata`. L'inserimento di un nuovo contatto avviene sempre in testa, se è il primo della lista, altrimenti in coda a partire dai successivi. Al momento non è possibile inserire in un punto della lista scelto. Ogni contatto ha un ID univoco generato automaticamente dal sistema. Gli altri argomenti da inserire sono:
    - nome 
    - cognome 
    - 1° telefono 
    - 2° telefono (facoltativo)
    - indirizzo (facoltativo)
    - città (se si ha scelto di inserire unn indirizzo andrà messa anche la città)
    - società (facoltativo)
    - email (facoltativo)
  
    I dati segnati come facoltativi prevedono che l'utente scelga se inserirli o meno.  

2) Per importare un contatto è necessario scrivere il nome del file in maniera molto precisa, se presente nella stessa cartella del programma. Se il file in cui è salvata la rubrica è in un'altra cartella andrà speciicato il percorso (assoluto o relativo).  Tuttavia si consiglia caldamente di conservare il file nella stessa cartella.  
3) La funzione che genera contatti random inserisce nella lista contatti completi (con tutti i dati sopraelencati). All'utente verrà richiesto solo quanti generarne.  
4) La scelta numero 4 riguarda le operazioni su singolo contatto, infatti si attiva appena viene inserito nella lista un contatto. Include un sottomenu di 4 scelte:
    - Cerca / stampa contatto -> cerca e stampa un contatto in base a 6 criteri:
        - primo della lista
        - ultimo della lista
        - ultimo inserito (diverso da ultimo della lista se questa viene ordinata)
        - cerca in base all'ID
        - cerca in base a nome e cognome del contatto
        - cerca in base al primo numero di telefono (ATTENZIONE: solo il primo, non il secondo)
    - Modifica contatto (le modifiche sono salvate automaticamente su file)
    - Cancella contatto (le modifiche sono salvate automaticamente su file)
    - Torna al menu principale
5) La scelta numero 5 riguarda le operazioni sulla rubrica, infatti si attiva appena vengono inseriti nella lista almeno 2 contatti. Include un sottomenu di 5 scelte:
    - Stampa la rubrica 
    - Ordina la rubrica (non ancora abilitata)
    - Salva la rubrica su file
    - Cancella la rubrica (permette di cancellare sia la rubrica in ram che quella su file)
    - Torna al menu principale  
  
6) Esce dal programma e cancella automaticamente la lista concatenata salvata in RAM.



#### Problematiche riscontrate ancora da risolvere

**ISSUE #1**  
Quando si aggiorna il file (si riscrive partendo da un punto salvato e non dal principio -> append)
il contatore nella funzione `salvaRubrica()` che risiede nel file libreria `menu5.h` conta sempre un contatto in piu: vale a dire se salvo 5 nuovi contatti il responso a video sarà: "6 contatti aggiunti"
  
**ISSUE #2**  
Dopo aver lanciato il salvataggio dei contatti, se lo si rilancia senza aver effettivamente aggiunto alcun contatto si avrà un messaggio che dice "1 nuovo contatto aggiunto".  
Sarebbe opportuno inserire un controllo affinchè se non ci sono nuovi contatti non viene fatto nulla:
- lettura file per confrontarlo con i dati in ram -> se coincidono non occorre il salvataggio  
  
&nbsp;  
Per ulteriori informazioni e necessità:  
fabrizio.ugo@edu.itspiemonte.it  
fazione33@gmail.com