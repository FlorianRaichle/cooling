/*
*   Funktionsdeklaration und Variablenuebergabe
*   
*   Numerik Praktikum Gruppe 2.1
*/

#ifndef header
#define header
 
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <cmath>
#include <fstream>

typedef std::vector <std::vector <double> > tabelle;
struct ergebnisse{
    std::string titel;
    std::vector <std::string> zeilen;
    std::vector <std::string> spalten;
    std::vector <std::vector <double> > daten;
};

extern const bool dev;
// Einlesen der Tabellenwerte
int read_file(std::string Name, tabelle& Daten);// a)

// Berechnung von Lambda mit Newton Verfahren
double colebrook(double lambda, double k, double V, double D, double c3);// b)
// Berechnung Durchmesser in Anhaengigkeit von lambda
double durchmesser(double Leistung, double Delta_p_einbaute, double V_ges, double V, double Laenge, double Lambda, double c1, double c2); // c)
// Auswahl Rohr
double Vergleich (tabelle& lief_Rohre, ergebnisse& durchmesser, ergebnisse& Wand); // d)
// Berechnung der Ventilstellung
void Ventileinstellungen (ergebnisse& Ventile, ergebnisse& Durchmesser, tabelle& Pumpen, tabelle& Stoffdaten, tabelle& Leitungen, double V_ges, double c3);

// Ausgabe in textdatei
void ausgabe(std::string Name, ergebnisse& Ergebnis, bool append = false); // f)

// Berechnung der Kosten pro Pumpe
double Gesamtkosten (double Pel, double Wirkungsgrad, double Betriebszeit, std::vector <double> d, tabelle& Rohre, tabelle& Parameter,std::vector <double> Wand);
// Erstellung des Polynomfit
double polyfit(int degree, std::vector <double>& x, std::vector <double>& y,  std::vector <double>& a); // g)
// Kostenfunktion als Ergebnis des Polynomfit
double kosten(std::vector <double> Parameter, double Leistung); // h) 
// Minimierung der Kostenfunktion
double minimum(double start, std::vector <double>& Parameter, int i = 0); // i)

// Newton-Verfahren
double newton(double lambda, std::function <double(double)> func);
// Polynom
double f(std::vector <double>&, double);

#endif