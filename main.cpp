/*
*   Numerik Praktikum Gruppe 2.1
*   Auslegung eines Kühlkreislaufs
*/

#include "header.h"
#include "tests.h"

const bool dev = true; // set true for debugging

int main(){
    // Speicher allokieren
    tabelle lief_Rohre;
    tabelle Pumpen;
    tabelle Leitungen;
    tabelle Kostenparameter;
    tabelle Stoffdaten;
    
    // Textdateinen einlesen
    read_file("data/rohre.txt", lief_Rohre);
    read_file("data/parameter.txt", Kostenparameter);
    read_file("data/Stoffdaten.txt", Stoffdaten);
    read_file("data/pumpen.txt", Pumpen);
    read_file("data/leitungen.txt", Leitungen);
    
    ergebnisse Innendurchmesser;
    Innendurchmesser.titel = "Durchmesser [m]";
    ergebnisse Ventile;
    Ventile.titel = "Ventilstellung [Pa]";
    ergebnisse Kosten;
    Kosten.titel = "Gesamtkosten [EUR]";
    
    // Berechnung Gesamtvolumenstrom
    double V_ges = 0;
    for(int i = 0; i < Leitungen.size(); i++){
        V_ges += Leitungen[i][0];
    }
    std::vector <int> del;
    double Lambda;
    // Berechnung Duchmesser und Lambda
    double c1 = (1E-6)*8*Stoffdaten[0][0];
    double c2 = (M_PI*M_PI);
    double c3 = (4*Stoffdaten[0][0]/(1E3*Stoffdaten[1][0]*M_PI));
    for (int i=0; i < Pumpen[0].size(); i++) { // gibt Dimension in x-Richtung dieser Tabelle an
        Innendurchmesser.daten.push_back(std::vector <double>());
        for (int j=0; j < Leitungen.size(); j++){
            // durchmesser(Leistung, Dichte, dp, V_ges, Durchfluss, Länge, Lambda)
            auto d =  std::bind(durchmesser, Pumpen[0][i], Leitungen[j][1], V_ges, Leitungen[j][0], Leitungen[j][2], std::placeholders::_1, c1, c2);
            // colebrook(Lambda, Dichte, Visc, k, Volumenstrom, Durchmesser)
            Lambda = newton(0.02, std::bind(colebrook,std::placeholders::_1, Leitungen[j][3], Leitungen[j][0], d, c3));
            // falls Fehler bei Berechnung von Lambda
            if(Lambda == -1){
                Innendurchmesser.daten[i].push_back(-1);
                del.push_back(i);
                break;
            }else{
                Innendurchmesser.daten[i].push_back(durchmesser(Pumpen[0][i], Leitungen[j][1], V_ges, Leitungen[j][0], Leitungen[j][2], Lambda, c1, c2));
                if(dev){
                    std::cout << i << " " << j << ": " << "Lambda: " << Lambda << " D: " << Innendurchmesser.daten[i][j] << std::endl;
                }
            }
        }
        Innendurchmesser.zeilen.push_back("Pumpe " + std::to_string(i+1));
        Ventile.zeilen.push_back("Pumpe " + std::to_string(i+1));
        Kosten.spalten.push_back("Pumpe " + std::to_string(i+1));
    }
    // lösche ungeeignete Pumpen
    for (int i = 0; i < del.size(); i++) {
        Pumpen[0].erase(Pumpen[0].begin()+del[i]-i);
        Pumpen[1].erase(Pumpen[1].begin()+del[i]-i);
        Innendurchmesser.daten.erase(Innendurchmesser.daten.begin()+del[i]-i);
        Innendurchmesser.zeilen.erase(Innendurchmesser.zeilen.begin()+del[i]-i);
        Ventile.zeilen.erase(Ventile.zeilen.begin()+del[i]-i);
        Kosten.spalten.erase(Kosten.spalten.begin()+del[i]-i);
        std::cout << "WARNUNG: Pumpe " + std::to_string(del[i]+1) + " nicht geeignet!" << std::endl;
    }
    
    ergebnisse Wand;
    // Vergleich mit lieferbaren Rohren
    Vergleich(lief_Rohre, Innendurchmesser, Wand);
    Ventileinstellungen(Ventile, Innendurchmesser, Pumpen, Stoffdaten, Leitungen, V_ges, c3);
    for (int i = 0; i < Innendurchmesser.daten[1].size(); i++){
        Innendurchmesser.spalten.push_back("Rohr " + std::to_string(i+1));
        Ventile.spalten.push_back("Rohr " + std::to_string(i+1));
    }
    ausgabe("Rohrauslegung.txt", Innendurchmesser);
    ausgabe("Rohrauslegung.txt", Ventile, true);
    
    // Kostenberechnung
    Kosten.daten.push_back(std::vector <double>());
    double Betriebszeit = 250 * 16 * 8;
    for (int i = 0; i < Pumpen[0].size(); i++){
        Kosten.daten[0].push_back(Gesamtkosten(Pumpen[0][i], Pumpen[1][i], Betriebszeit, Innendurchmesser.daten[i], Leitungen, Kostenparameter, Wand.daten[i]));
    }
    // Ausgabe der Stützstellen
    ausgabe("Kosten.txt", Kosten);
    
    // Polynomfit
    // Varianz von y
    double mean = 0;
    for (int i = 0; i < Kosten.daten[0].size(); i++) {
        mean += Kosten.daten[0][i];
    }
    mean /= Kosten.daten[0].size();
    double tot = 0;
    for (int i = 0; i < Kosten.daten[0].size(); i++) {
        tot += (Kosten.daten[0][i] - mean) * (Kosten.daten[0][i] - mean);
    }
    int degree;
    std::cout << "Polynomgrad: ";
    std::cin >> degree;
    ergebnisse a;
    a.daten.push_back(std::vector <double>(degree+1, 1));
    double res = polyfit(degree, Pumpen[0], Kosten.daten[0], a.daten[0]);
    // Ausgabe R^2 (optional)
    if(dev) std::cout << "R^2: " << 1-res/tot << std::endl;
    for (int i = 0; i < a.daten[0].size(); i++){
        a.spalten.push_back("a" + std::to_string(i));
    }
    a.titel = {"Parameter des Polynoms"};
    ausgabe("parameter.txt", a);
    
    // Ermittlung der optimalen Leistung
    ergebnisse Pumpe;
    Pumpe.titel = "optimale Pumpe";
    Pumpe.spalten.push_back("Leistung [kW]");
    Pumpe.daten.push_back(std::vector<double>(1));
    double min = Pumpen[0][Pumpen[0].size()];
    double min1;
    for(int i = 10; i < Pumpen[0][Pumpen[0].size()-1]; i += 10){
        min1 = min;
        min = minimum(i, a.daten[0]);
        if(f(a.daten[0], min1) - f(a.daten[0], min) > 1){
            Pumpe.daten[0][0] = min;
            if(dev) std::cout << "Minimum bei " << min << std::endl;
        }
    }
    // Ausgabe der Pumpenleistung
    ausgabe("Ergebnis.txt",Pumpe);
}