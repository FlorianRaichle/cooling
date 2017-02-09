/*
*   Auswahl der Rohre und Berechnung des Druckverlusts
*/

#include "header.h"
using namespace std;

void Vergleich(tabelle& lief_Rohre, ergebnisse& durchmesser, ergebnisse& Wand) {
	for (int i = 0; i <durchmesser.daten.size(); i++) {
		Wand.daten.push_back(std::vector <double>());
		for (int j = 0; j < durchmesser.daten[i].size(); j++) {
			//Liegt der Durchmesser nicht im Bereich lieferbarer Rohre wird null aussgegeben
			if (durchmesser.daten[i][j] < lief_Rohre[0][0] / 1000 || durchmesser.daten[i][j] > lief_Rohre[lief_Rohre.size() - 1][0] / 1000) {
				durchmesser.daten[i][0] = 0;
			}
			else {
				//Liegt der berechnete Durchmesser zwischen den Durchmessern zweier lieferbarer Rohre so wird der nächst größere gewählt
				for (int k = 0; k < lief_Rohre.size(); k++) {
					if (durchmesser.daten[i][j] <= lief_Rohre[k][0] / 1000) {
						durchmesser.daten[i][j] = lief_Rohre[k][0] / 1000;
						Wand.daten[i].push_back(lief_Rohre[k][1] / 1000);
						break;
					}
				}
			}
		}
	}
}

// Berechne Ventileinstellungen

void Ventileinstellungen(ergebnisse& Ventile, ergebnisse& Durchmesser, tabelle& Pumpen, tabelle& Stoffdaten, tabelle& Leitungen, double V_ges, double c3) {
	double Widerstandszahl, delta_p_Reibung, delta_p_gesamt;
	for (int i = 0; i < Durchmesser.daten.size(); i++) {
		Ventile.daten.push_back(vector <double>());
		delta_p_gesamt = 1E6*Pumpen[0][i] / V_ges;
		for (int j = 0; j < Durchmesser.daten[i].size(); j++) {
			//Berechnung reales Widerstandszahl mit Newtonverfahren
			Widerstandszahl = newton(0.02, std::bind(colebrook, std::placeholders::_1, Leitungen[j][3], Leitungen[j][0], Durchmesser.daten[i][j], c3));

			//Berechnung der durch Reibung verursachten Druckverluste
			delta_p_Reibung = (1E-6)*Widerstandszahl*Leitungen[j][2] * Stoffdaten[0][0] * 8 * Leitungen[j][0] * Leitungen[j][0] / (pow(Durchmesser.daten[i][j], 5)*M_PI*M_PI);

			//Berechung des von dem Ventil zu erzeugenden Druckverlust
			Ventile.daten[i].push_back(delta_p_gesamt - (1E5)*Leitungen[j][1] - delta_p_Reibung);
		}
	}
}
