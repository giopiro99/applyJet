#include "httplib.h"
#include "Calculator.hpp"
#include <iostream>
#include <sstream>
#include <string>

std::string build_json_response(const Calculator& calc) {
	std::stringstream ss;

	// Costruzione manuale del JSON. 
	ss << "{"
		<< "\"netto_annuale\": " << calc.getNettoAnnuale() << ","
		<< "\"netto_mensile\": " << calc.getNettoMensile() << ","
		<< "\"totale_trattenute\": " << calc.getTotaleTrattenute() << ","
		<< "\"irpef_netta\": " << calc.getIrpefNetta() << ","
		<< "\"irpef_lorda\": " << calc.getIrpefLorda() << ","
		<< "\"imponibile_irpef\": " << calc.getImponibileIRPEF() << ","
		<< "\"trattenute_inps\": " << calc.getTrattenuteINPS()
		<< "}";
	return ss.str();
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
			res.status = 500;
			res.set_content("{\"error\": \"Errore nel calcolo\"}", "application/json");
		}
	});
	std::cout << "Server in ascolto su 0.0.0.0:3000..." << std::endl;
	svr.listen("0.0.0.0", 3000);
	return 0;
}