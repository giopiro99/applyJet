# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    main.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpirozzi <gpirozzi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 14:17:34 by gpirozzi          #+#    #+#              #
#    Updated: 2025/12/05 15:40:36 by gpirozzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

class	Calculator:
	def __init__(self, ral_input):
		self.ral = float(ral_input)
		self.aliquota_inps = 0.0919
		self.netto_annuale = 0.0
		self.irpef_lorda = 0.0
		self.irpef_netta = 0.0
		self.detrazioni = 0.0
		self.imponibile_irpef = 0.0
		self.contributi_previdenziali = 0.0
		self.addizionale_comunale_milano = 0.0080
		self.addizionale_regionale_lombardia = 0.0123
		self.addizionale_totale = 0.0

	def calculate_contributi_previdenziali(self):
		self.contributi_previdenziali = self.ral * self.aliquota_inps
		return

	def calculate_imponibile_irpef(self):
		self.imponibile_irpef = self.ral - self.contributi_previdenziali
		return

	def calculate_irpef_lorda(self):
		reddito_residuo = float(self.imponibile_irpef)
		scaglione_max = 50000.0
		scaglione_min = 28000.0

		if reddito_residuo > scaglione_max:
			reddito_residuo = reddito_residuo - scaglione_max
			self.irpef_lorda += reddito_residuo * 0.43
			reddito_residuo = scaglione_max
		if reddito_residuo > scaglione_min and reddito_residuo <= scaglione_max:
			reddito_residuo = reddito_residuo - scaglione_min
			self.irpef_lorda += reddito_residuo * 0.35
			reddito_residuo = scaglione_min
		if reddito_residuo > 0:
			self.irpef_lorda += reddito_residuo * 0.23
		return

	def calculate_detrazioni(self):
		detrazione_base = 1910.0
		bonus_seconda_fascia = 1190.0
		scaglione_max = 50000.0
		scaglione_mid = 28000.0
		scaglione_min = 15000.0

		ampiezza_scaglione_1 = 22000.0
		ampiezza_scaglione_2 = 13000.0

		if self.imponibile_irpef > scaglione_max:
			self.detrazioni = 0.0
		elif self.imponibile_irpef > scaglione_mid and self.imponibile_irpef <= scaglione_max:
			self.detrazioni = detrazione_base * ((scaglione_max - self.imponibile_irpef) / ampiezza_scaglione_1)
		elif self.imponibile_irpef > scaglione_min and self.imponibile_irpef <= scaglione_mid:
			self.detrazioni = detrazione_base + bonus_seconda_fascia * ((scaglione_mid - self.imponibile_irpef) / ampiezza_scaglione_2)
		elif self.imponibile_irpef <= scaglione_min:
			self.detrazioni = detrazione_base
		return

	def calculate_irpef_netta(self):
		self.irpef_netta =  max(0.0, self.irpef_lorda - self.detrazioni)
		return

	def calculate_addizionali(self):
		self.addizionale_totale = (self.addizionale_regionale_lombardia * self.imponibile_irpef) + (self.addizionale_comunale_milano * self.imponibile_irpef)
		return

	def calculate_ral_netta(self):
		self.netto_annuale = self.ral - self.contributi_previdenziali - self.irpef_netta - self.addizionale_totale
		return

	def calculate_all(self):
		self.calculate_contributi_previdenziali()
		self.calculate_imponibile_irpef()
		self.calculate_irpef_lorda()
		self.calculate_detrazioni()
		self.calculate_irpef_netta()
		self.calculate_addizionali()
		self.calculate_ral_netta()
		return

if __name__ == "__main__":
	calc = Calculator(35000)
	calc.calculate_all()
	print(f"CONTRIBUTI INPS {calc.contributi_previdenziali:.2f}")
	print(f"IRPEF NETTA {calc.irpef_netta:.2f}")
	print(f"DETRAZIONI {calc.detrazioni:.2f}")
	print(f"NETTO ANNUALE {calc.netto_annuale:.2f}")
	print(f"NETTO MENSILE {calc.netto_annuale / 13:.2f}")