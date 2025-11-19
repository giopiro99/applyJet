Compito del progetto:
immagina di essere un product builder a Jet HR. Ti viene chiesto di costruire un prototipo che simula la proiezione di retribuzione netta annuale partendo da una retribuzione lorda annuale, e mostra tutte le voci che devono essere trattenute al lordo.
Il risultato sarà un calcolatore che riceve in input una RAL e in output ti dice quanto è il netto annuale e mensile che percepisce il dipendente e quanto sono le tasse che deve pagare.
Sappiamo bene che il dominio è molto vasto e che il prototipo non può coprire tutti i casi e fare uso delle logiche precise. Quello che ci aspettiamo è un prototipo funzionante in un caso semplice e standard, il che vuol dire che puoi fare tutte le semplificazioni e scelte che ritieni opportune. Ad esempio, puoi assumere che:
- il dipendente è un impiegato a tempo indeterminato
- il dipendente vive a Milano
- il dipendente non ha nessun tipo di agevolazione particolare
Ogni altra semplificazione fatta sarà discussa durante una possibile interview.
**Outcome**
L’outcome dovrà essere una pagina web in cui l’utente possa mettere degli input e cliccando “calcola” possa vedere in pagina gli output richiesti.

**tecnologie utilizzate**
C++11: Core logic per il calcolo finanziario (scaglioni IRPEF, detrazioni, INPS).
cpp-httplib: Libreria header-only per trasformare il calcolatore C++ in un servizio REST.
Docker & Docker Compose: Per la containerizzazione, l'isolamento dell'ambiente e l'orchestrazione dei servizi.
Nginx: Utilizzato sia come web server per i file statici che come reverse proxy.
HTML5 / JavaScript (Vanilla): Interfaccia utente essenziale e performante.

**Struttura del progetto pensata da me:**
```text
applyJet/
├── Makefile                # Comandi rapidi per build e pulizia
├── docker-compose.yml      # Orchestrazione dei 3 servizi
│
├── applybackend/           # SERVIZIO BACKEND (C++)
│   ├── main.cpp            # Server HTTP e gestione API (routing)
│   ├── Calculator.cpp/hpp  # Logica di dominio (calcoli finanziari)
│   ├── httplib.h           # Libreria server HTTP
│   └── Dockerfile          # Build multi-stage del servizio C++
│
├── applyfrontend/          # SERVIZIO FRONTEND
│   ├── index.html          # Interfaccia utente
│   ├── script.js           # Logica client e chiamata fetch()
│   └── Dockerfile          # Container Nginx per file statici
│
└── applyserver/            # SERVIZIO PROXY
    ├── server.conf         # Configurazione routing Nginx
    └── Dockerfile          # Container Nginx

**comandi**
make build -> costruisce i container
make up -> fa partire i container
make down -> stoppa i container
make all -> fa tutti e 3 i comandi insieme
make fclean -> cancella la/e immagine/i docker create
make re -> make fclean + make all

**senza make file**
docker compose up --build -d
docker compose down

**dopo aver fatto partire i container**:
Accedi al Calcolatore: Apri il browser e visita: https://localhost:8443

Note:
-Non sono inclusi esoneri contributivi temporanei, detrazioni per carichi di famiglia o TFR per semplicita'.
-É presente la cartella secrets con i file delle chiavi ssl per comodità, so che in un ambiente di sviluppo reale essi non dovrebbero essere nella repo.
