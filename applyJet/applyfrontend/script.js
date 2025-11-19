document.addEventListener('DOMContentLoaded', () => {
    const ralInput = document.getElementById('ralInput');
    const calculateBtn = document.getElementById('calculateBtn');
    const resultsDiv = document.getElementById('resultsDiv');
    const errorMessage = document.getElementById('errorMessage');
    const loadingMessage = document.getElementById('loadingMessage');
    const nettoAnnualeSpan = document.getElementById('nettoAnnuale');
    const nettoMensileSpan = document.getElementById('nettoMensile');
    const totaleTrattenuteSpan = document.getElementById('totaleTrattenute');
    const irpefNettaSpan = document.getElementById('irpefNetta');
    const irpefLordaSpan = document.getElementById('irpefLorda');
    const imponibileIRPEFSpan = document.getElementById('imponibileIRPEF');
    const trattenuteINPSSpan = document.getElementById('trattenuteINPS');

    // Funzione per formattare i numeri come valuta
    const formatCurrency = (value) => {
        if (typeof value !== 'number' || isNaN(value)) {
            return 'error in format currency';
        }
        return value.toLocaleString('it-IT', { style: 'currency', currency: 'EUR' });
    };
    calculateBtn.addEventListener('click', async () => {
        errorMessage.textContent = '';
        resultsDiv.style.display = 'none';
        loadingMessage.style.display = 'block';
        const ral = parseFloat(ralInput.value);

        if (isNaN(ral) || ral <= 0) {
            errorMessage.textContent = 'Per favore, inserisci una RAL valida e positiva.';
            loadingMessage.style.display = 'none';
            return;
        }

        try {
            // Indirizzo dell'API del backend
            const response = await fetch('/api/calcola', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ ral: ral }),
            });
            loadingMessage.style.display = 'none';
            if (!response.ok) {
                const errorData = await response.json();
                throw new Error(errorData.error || 'Errore durante il calcolo.');
            }
            const data = await response.json();
            // Aggiorna i risultati sulla pagina
            nettoAnnualeSpan.textContent = formatCurrency(data.netto_annuale);
            nettoMensileSpan.textContent = formatCurrency(data.netto_mensile);
            totaleTrattenuteSpan.textContent = formatCurrency(data.totale_trattenute);
            irpefNettaSpan.textContent = formatCurrency(data.irpef_netta);
            irpefLordaSpan.textContent = formatCurrency(data.irpef_lorda);
            imponibileIRPEFSpan.textContent = formatCurrency(data.imponibile_irpef);
            trattenuteINPSSpan.textContent = formatCurrency(data.trattenute_inps);
            resultsDiv.style.display = 'block';
        } catch (error) {
            loadingMessage.style.display = 'none';
            errorMessage.textContent = `Errore: ${error.message}`;
            console.error('Fetch error:', error);
        }
    });
});