#include "Calculator.hpp"
#include <stdexcept>

/*===============CONSTRUCTOR===============*/
Calculator::Calculator( double ral) :
								_ral(ral), _trattenuteINPS(0.0),
								_imponibileIRPEF(0.0), _irpefLorda(0),
								_irpefNetta(0.0), _totaleTrattenute(0.0),
								_detrazioni(0.0), _nettoAnnuale(0.0),
								_nettoMensile(0.0) {}

Calculator::Calculator(const Calculator& other) :
								_ral(other._ral), _trattenuteINPS(other._trattenuteINPS), 
								_imponibileIRPEF(other._imponibileIRPEF), _irpefLorda(other._irpefLorda),
								_detrazioni(other._detrazioni), _nettoAnnuale(other._nettoAnnuale),
								_nettoMensile(other._nettoMensile) {}

/*===============OPERATOR===============*/
Calculator&	Calculator::operator=(const Calculator& other)
{
	if (this != &other)
	{
		_ral = other._ral;
		_trattenuteINPS = other._trattenuteINPS; 
		_imponibileIRPEF = other._imponibileIRPEF;
		_irpefLorda = other._irpefLorda;
		_detrazioni = other._detrazioni;
		_nettoAnnuale = other._nettoAnnuale;
		_nettoMensile = other._nettoMensile;
	}
	return (*this);
}

/*===============METHODS===============*/
void	Calculator::calculateTrattenuteINPS()
{
	double tmpRal = _ral;

	if (hasBenefit)
		tmpRal += benefit;
	_trattenuteINPS = tmpRal * _aliquotaStandard;
}

void	Calculator::calculateImponibileIRPEF()
{

	_imponibileIRPEF = _ral - _trattenuteINPS;

	if (hasBenefit)
		_imponibileIRPEF += benefit;

	if (_imponibileIRPEF < 0.0)
		throw std::runtime_error("something get wrong in calculate IMPONIBILE IRPEF");
}

/* L'IRPEF Lorda si calcola applicando le aliquote marginali per scaglioni sul tuo Imponibile IRPEF.*/
void	Calculator::calculateIrpefLorda()
{
	//Scaglioni:
	//reddito residuo > 0 ALIQUOTA_1
	//reddito residuo > 28000 ALIQUOTA_2
	//reddito residuo > 50000 ALIQUOTA_3

	//Calcolo in cascata perche' l irpef lorda si calcola ogni volta
	//sull eccedenza di quello scaglione e si va a scendere
	
	const double ALIQUOTA_1 = 0.23;
	const double ALIQUOTA_2 = 0.35;
	const double ALIQUOTA_3 = 0.43;
	
	double redditoResiduo = _imponibileIRPEF;
	double IRPEF_LORDA = 0.0;
	double eccedenza = 0.0;

	if (redditoResiduo > 50000.0)
	{
		eccedenza = (redditoResiduo - 50000.0);
		IRPEF_LORDA += eccedenza * ALIQUOTA_3;
		redditoResiduo = 50000.0;
	}

	if (redditoResiduo > 28000.0)
	{
		eccedenza = (redditoResiduo - 28000.0);
		IRPEF_LORDA += eccedenza * ALIQUOTA_2;
		redditoResiduo = 28000.0;
	}

	if (redditoResiduo > 0.0)
		IRPEF_LORDA += redditoResiduo * ALIQUOTA_1;

	_irpefLorda = IRPEF_LORDA;

	//controllo eventuali bug nel calcolo
	if (IRPEF_LORDA <= 0.0)
		throw std::runtime_error("Something get wrong in calculate IRPEF_LORDA");
}

void Calculator::calculateDetrazioni()
{
	const double DETRAZIONE_BASE_GARANTITA = 1910.0;
	const double BONUS_SECONDA_FASCIA = 1190.0;
	const double LIMITE_1 = 50000.0;
	const double LIMITE_2 = 28000.0;
	const double LIMITE_3 = 15000.0;

	if (_imponibileIRPEF >= LIMITE_1)
		_detrazioni = 0.0;
	else if (_imponibileIRPEF > LIMITE_2)
		_detrazioni = DETRAZIONE_BASE_GARANTITA * ((LIMITE_1 - _imponibileIRPEF) / 22000.0);
	else if (_imponibileIRPEF > LIMITE_3)
		_detrazioni = DETRAZIONE_BASE_GARANTITA + BONUS_SECONDA_FASCIA * (LIMITE_2 - _imponibileIRPEF) / 13000.0;
	else if (_imponibileIRPEF > 0.0)
		_detrazioni = DETRAZIONE_BASE_GARANTITA;
}

void	Calculator::calculateTotaleTrattenute()
{
	double addizionaleRegionale = _imponibileIRPEF * 0.0123; //1.23% per la lombardia
	double addizionaleComunale = _imponibileIRPEF * 0.0080; //0.80% per MILANO

	_totaleTrattenute = _irpefNetta + _trattenuteINPS + addizionaleRegionale + addizionaleComunale;
}

void	Calculator::calculateNettoAnnuale()
{
	_nettoAnnuale = _ral - _totaleTrattenute;
}

void	Calculator::calculateNettoMensile()
{
	_nettoMensile = (_nettoAnnuale / 13); // se consideriamo la 13esima
}

void	Calculator::calculateIrpefNetta()
{
	calculateDetrazioni();
	if (_detrazioni < 0.0)
		throw std::runtime_error("Something get wrong in calculate DETRAZIONI");

	_irpefNetta = std::max(0.0, _irpefLorda - _detrazioni);
}

void	Calculator::calculateAll()
{
	calculateTrattenuteINPS();
	calculateImponibileIRPEF();
	calculateIrpefLorda();
	calculateIrpefNetta();
	calculateTotaleTrattenute();
	calculateNettoAnnuale();
	calculateNettoMensile();
}

/*===============GETTERS===============*/
const double&	Calculator::getTrattenuteINPS() const { return (_trattenuteINPS); }

const double&	Calculator::getImponibileIRPEF() const{ return (_imponibileIRPEF); }

const double&	Calculator::getIrpefLorda() const{ return (_irpefLorda); }

const double&	Calculator::getIrpefNetta() const { return (_irpefNetta); }

const double&	Calculator::getTotaleTrattenute() const { return (_totaleTrattenute); }

const double&	Calculator::getNettoAnnuale() const { return (_nettoAnnuale); }

const double&	Calculator::getNettoMensile() const { return (_nettoMensile); }

/*===============DESTRUCTOR===============*/
Calculator::~Calculator() {}