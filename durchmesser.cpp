#include "header.h"
using namespace std;

double durchmesser(double Leistung, double Dichte, double Delta_p_einbaute, double V_ges, double V, double Laenge, double Lambda) { 

    double d = pow(((1E-6)*8*Lambda*Dichte*Laenge*V*V)/((M_PI*M_PI)*((1E6*Leistung/V_ges)-(1E5)*Delta_p_einbaute)), 0.2);
    if (d <= 0) {
        cout << " Unrealistische Durchmesserwerte. Bitte Daten überprüfen." << endl;
    }
    return d;
}