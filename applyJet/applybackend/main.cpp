#include "httplib.h"        // Include la libreria header-only per creare il server HTTP
#include "Calculator.hpp"   // Include la tua classe Calculator con la logica finanziaria
#include <iostream>         // Per input/output standard (std::cout, std::cerr)
#include <sstream>          // Per costruire stringhe complesse (come il JSON)
#include <iomanip>          // Per formattare i numeri (std::fixed, std::setprecision)
#include <string>           // Per la gestione delle stringhe

std::string build_json_response(const Calculator& calc) {
	std::stringstream ss;
	// Costruzione manuale del JSON. 
	// std::fixed e std::setprecision(2) assicurano che i numeri abbiano sempre 2 decimali (formato valuta).
	ss << "{"
		<< "\"netto_annuale\": " << std::fixed << std::setprecision(2) << calc.getNettoAnnuale() << ","
		<< "\"netto_mensile\": " << std::fixed << std::setprecision(2) << calc.getNettoMensile() << ","
		<< "\"totale_trattenute\": " << std::fixed << std::setprecision(2) << calc.getTotaleTrattenute() << ","
		<< "\"irpef_netta\": " << std::fixed << std::setprecision(2) << calc.getIrpefNetta() << ","
		<< "\"irpef_lorda\": " << std::fixed << std::setprecision(2) << calc.getIrpefLorda() << ","
		<< "\"imponibile_irpef\": " << std::fixed << std::setprecision(2) << calc.getImponibileIRPEF() << ","
		<< "\"trattenute_inps\": " << std::fixed << std::setprecision(2) << calc.getTrattenuteINPS()
		<< "}";
	return ss.str();
	// Restituisce la stringa costruita dallo stream
}

int main(void)
{
	// Crea l'istanza del server HTTP fornita dalla libreria cpp-httplib
	httplib::Server svr;
	// Definisce una rotta (endpoint) che risponde solo alle richieste HTTP POST
	// L'URL è "/api/calcola".
	svr.Post("/api/calcola", [](const httplib::Request& req, httplib::Response& res)
	{
		try
		{
			std::string body = req.body;
			std::string key = "\"ral\":";
			size_t start_pos = body.find(key);
			if (start_pos == std::string::npos)
				throw std::runtime_error("Chiave 'ral' non trovata nel JSON"); // Errore se non c'è la chiave
			size_t value_pos = start_pos + key.length();

			// Cerca la fine del valore numerico.
			// Il valore finisce quando incontriamo una virgola (se ci sono altri campi) 
			// o una parentesi graffa chiusa (se è l'ultimo campo).
			size_t end_pos = body.find_first_of(",}", value_pos);
			std::string ral_str;
			if (end_pos != std::string::npos)
				ral_str = body.substr(value_pos, end_pos - value_pos);
			else
				ral_str = body.substr(value_pos);

			double ral = std::stod(ral_str);
			Calculator calculator(ral);
			calculator.calculateAll();

			std::string json_response = build_json_response(calculator);
			
			// Imposta il corpo della risposta HTTP e l'header Content-Type
			res.set_content(json_response, "application/json");
		}
		catch (const std::exception& e)
		{
			std::cerr << "[ERROR] " << e.what() << std::endl;
			// Imposta lo status code HTTP a 500 (Internal Server Error)
			res.status = 500;
			// Invia un JSON di errore al client per non rompere il frontend
			res.set_content("{\"error\": \"Errore nel calcolo\"}", "application/json");
		}
	});

	// Avvia il server e lo mette in ascolto.
	// "0.0.0.0" significa che ascolta su tutte le interfacce di rete (necessario per Docker).
	// 3000 è la porta interna del container.
	std::cout << "Server in ascolto su 0.0.0.0:3000..." << std::endl;
	svr.listen("0.0.0.0", 3000);
	return 0;
}