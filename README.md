# Prototipo Calcolatore Busta Paga (Jet HR Task)

Un prototipo full-stack progettato per simulare il calcolo della retribuzione netta (annuale e mensile) a partire dalla RAL, evidenziando le trattenute fiscali e previdenziali secondo il sistema italiano.

## Obiettivo
Il calcolatore riceve in input una RAL e restituisce output dettagliati (Netto, IRPEF, INPS), in un'interfaccia web semplice e reattiva.

Il progetto copre un caso d'uso "Standard" con le seguenti assunzioni:
* **Profilo:** Impiegato a tempo indeterminato.
* **Residenza:** Milano.
* **Semplificazioni:** Non sono inclusi esoneri contributivi temporanei, detrazioni per carichi di famiglia o TFR.

## Tecnologie Utilizzate

* **C++11:** Core logic per il calcolo finanziario (scaglioni IRPEF, detrazioni, INPS).
* **cpp-httplib:** Libreria header-only per esporre la logica C++ come API REST.
* **Docker & Docker Compose:** Per la containerizzazione e l'orchestrazione dell'ambiente.
* **Nginx:** Reverse Proxy e Web Server per i file statici.
* **HTML5 / JavaScript (Vanilla):** Interfaccia utente essenziale.


## comandi
***make build -> costruisce i container***
***make up -> fa partire i container***
***make down -> stoppa i container***
***make all -> fa tutti e 3 i comandi insieme***
***make fclean -> cancella la/e immagine/i docker create***
***make re -> make fclean + make all***

### se non vuoi utilizzare il makefile
***docker compose up --build -d***
***docker compose down***

### dopo aver fatto partire i container:
***Accedi al Calcolatore: Apri il browser e visita: https://localhost:8443***

### Nota:
***-É presente la cartella secrets con i file delle chiavi ssl per comodità, so che in un ambiente di sviluppo reale essi non dovrebbero essere nella repo.***


### Struttura del Progetto

```text
applyJet/
├── Makefile                # Comandi rapidi per build e pulizia
├── docker-compose.yml      # Orchestrazione dei 3 servizi
│
├── applybackend/           # BACKEND C++
│   ├── main.cpp            # Server HTTP e gestione API
│   ├── Calculator.cpp/hpp  # Logica di dominio finanziario
│   ├── httplib.h           # Libreria server
│   └── Dockerfile          # Build multi-stage
│
├── applyfrontend/          # FRONTEND
│   ├── index.html          # UI del Calcolatore
│   ├── script.js           # Logica client e fetch API
│   └── Dockerfile          # Server Nginx statico
│
├── applyserver/            # PROXY
    ├── server.conf         # Configurazione routing
    └── Dockerfile          # Nginx Gateway
