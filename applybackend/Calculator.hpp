#ifndef CALCULATOT_HPP
# define CALCULATOT_HPP

/* FORMULE, DEFINIZIONI E FONTI

	FORMULE:
		-TRATTENUTE_INPS = RAL * 0,0919
		-IMPONIBILE_IRPEF = RAL - Trattenuta INPS
		-IRPEF_LORDA: ECCEDENZA * ALIQUOTA_CORRENTE [poi a scendere su ogni scaglione]
			*reddito residuo > 0 ALIQUOTA_1=>23%
			*reddito residuo > 28000 ALIQUOTA_2=>35%
			*reddito residuo > 50000 ALIQUOTA_3=>43%
		-IRPEF Netta = IRPEF Lorda - Detrazioni
			-DETRAZIONI:
				*Fascia ALTA (R > 50000) = 0
				*Fascia MEDIA-ALTA (R > 28000) = 1910 * ((50000 - R) / 22000)
				*Fascia MEDIA (R > 15000) = 1910 + 1190 * ((28000 - R) / 13000)
				*Fascia BASSA (R > 0) = 1910
		-TOTALE TRATTENUTE = IRPEF_NETTA + TRATTENUTE_INPS + ADD_REGIONALE + ADD_COMUNALE;
		-NETTO ANNUALE = RAL - TOTALE_TRATTENUTE
	DEFINIZIONI:
		TRATTENUTE_INPS:
			-La contribuzione previdenziale consiste, quindi, in un “premio assicurativo”
			che si paga per assicurare il lavoratore per un determinato evento come la malattia,
			la maternità, la disoccupazione o la pensione, etc. 
			FONTE:https://www.inps.it/it/it/inps-comunica/diritti-e-obblighi-in-materia-di-sicurezza-sociale-nell-unione-e/per-le-imprese/contributi-previdenziali.html
		-IRPEF:
			-Imposta sul reddito delle persone fisiche.
			Ciò implica che, tra le tante imposte presenti nel sistema tributario italiano,
			l’IRPEF è quella che accomuna tutti i contribuenti, poiché è tenuta a pagarla praticamente chiunque abbia un reddito,
			dai dipendenti ai lavoratori autonomi.
			La progressività dell’imposta si esprime proprio tramite gli scaglioni, ognuno con un valore minimo e con un valore
			massimo in cui si paga una specifica aliquota percentuale: il reddito oltre il valore massimo di uno scaglione verrà
			dunque tassato secondo l’aliquota immediatamente successiva. Per fare un esempio e capire come calcolare l’IRPEF,
			ipotizziamo che il reddito imponibile sia di  30.000 euro.
			In questo caso, l’imposta lorda è uguale al 23% per i primi 28.000 euro più il 35% per i restanti 2.000 euro.
			FONTE:https://www.teamsystem.com/magazine/glossario/irpef/
*/

class Calculator
{
	private:
			static constexpr double	_aliquotaStandard = 0.0919; /* 9.19% */

			double	_ral;
			double	_trattenuteINPS;
			double	_imponibileIRPEF;
			double	_irpefLorda;
			double	_irpefNetta;
			double	_totaleTrattenute;
			double	_detrazioni;
			double	_nettoAnnuale;
			double	_nettoMensile;

			void	calculateTrattenuteINPS();
			void	calculateImponibileIRPEF();
			void	calculateIrpefLorda();
			void	calculateIrpefNetta();
			void	calculateTotaleTrattenute();
			void	calculateNettoAnnuale();
			void	calculateNettoMensile();
			void	calculateDetrazioni();
			Calculator() {};
	public:
			Calculator( double );
			Calculator( const Calculator& other);
			Calculator& operator=(const Calculator& other);
			~Calculator();

			const double&	getTrattenuteINPS() const;
			const double&	getImponibileIRPEF() const;
			const double&	getIrpefLorda() const;
			const double&	getIrpefNetta() const;
			const double&	getTotaleTrattenute() const;
			const double&	getNettoAnnuale() const;
			const double&	getNettoMensile() const;
			void	calculateAll();
};

#endif