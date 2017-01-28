/*
*   Berechnung der Gesamtkosten deiner Pumpe
*
*/

#include "header.h"
using namespace std;

double Pumpenkosten (double P_mech, double Wirkungsgrad, vector <double> Parameter) {       
    return(Parameter[0]*P_mech/Wirkungsgrad)+Parameter[1]*(Parameter[2]-Wirkungsgrad);
}

double Rohrkosten(vector <double> d, tabelle Leitungen, vector <double> Parameter,std::vector <double> Wand) {
    double Kr = 0;
    double D;
    for (int i=0; i < d.size(); i++) {
        D = d[i]+2*Wand[i];
        Kr+=((D*D*Parameter[0])-(D*Parameter[1])+Parameter[2])*Leitungen[i][2];
    }
    return Kr;
    
}

double Stromkosten (double Betriebszeit, double P_mech, vector <double> Parameter, double Wirkungsgrad){
    return Parameter[0]*Betriebszeit*P_mech/Wirkungsgrad;
}

double Gesamtkosten (double P_mech, double Wirkungsgrad, double Betriebszeit, vector <double> d,tabelle& Leitungen, tabelle& Parameter, std::vector <double> Wand) {
    return Pumpenkosten(P_mech, Wirkungsgrad, Parameter[0]) + Rohrkosten(d, Leitungen, Parameter[1], Wand) + Stromkosten(Betriebszeit, P_mech, Parameter[2], Wirkungsgrad);
}