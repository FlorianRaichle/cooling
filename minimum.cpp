/*
*   Minimumsberechnung
*/
#include "header.h"
using namespace std;

double poly (vector <double>& array, double x){  //1.Ableitung berechnen
    double f = 0;
    for (int i = 1; i < array.size(); i++) {
        f += i*array[i]* pow(x,(i-1));
    }
    return f;
    
}
double minimum (double start, vector <double>& array, int i){
   
    // Abbruch
    if (i > 15) return -1;
    // Polnomgrad 1
    if(array.size() < 3){
        cout << "Kein Minimum vorhanden" << endl;
        return -1;
    }
    // Nullstelle der 1. Ableitung wird berechnet
    double min = newton(start, bind(poly, array, placeholders::_1));
     // überprüfen ob es sich um Minimum handelt
    if (poly(array, min-0.1)<0 && poly(array, min+0.1) > 0){
         //x-Wert des Minimums ausgeben
        return min;
    }else if(min == -1){
        cout << "Kein Minimum gefunden" << endl;
        return -1;
    }
    else{
        minimum(start+10, array, ++i);
    }
}