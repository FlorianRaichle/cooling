/*
*   Colebrook-Formel zur Berechnung der Widerstandszahl
*   Berechnung des Durchmessers
*   Newton-Verfahren
*/
#include "header.h"

double durchmesser(double Leistung, double Delta_p_einbaute, double V_ges, double V, double Laenge, double Lambda, double c1, double c2) {
    //double d = pow(((1E-6)*8*Lambda*Dichte*Laenge*V*V)/((M_PI*M_PI)*((1E6*Leistung/V_ges)-(1E5)*Delta_p_einbaute)), 0.2);
    double d = pow((c1*Lambda*Laenge*V*V)/(c2*((1E6*Leistung/V_ges)-(1E5)*Delta_p_einbaute)), 0.2);
    if (d <= 0) {
        std::cout << " Unrealistische Durchmesserwerte. Bitte Daten überprüfen." << std::endl;
    }
    return d;
}

double colebrook(double lambda, double k, double V, double D, double c3){
    // return 1.74-2*std::log10((2*k/(1E3*D))+(18.7/((4*Dichte*V/(1E3*Visc*D*M_PI))*pow(lambda,0.5))))-(1/pow(lambda,0.5));
    return 1.74-2*std::log10((2*k/(1E3*D))+(18.7/(c3*(V/D)*pow(lambda,0.5))))-(1/pow(lambda,0.5));
}

double ableitung(double x, std::function <double (double)> f){
    double h = 0.01;
    double y = 1;
    double y1 = 1.1;
    while (std::abs(1-(y / y1)) > 0.001){
        y1 = y;
        y = (f(x+h)-f(x))/h;
        h = h/10;
    }
    return y;
}

double newton(double lambda, std::function<double (double)> func){
    double lambda1 = 1;
    while (std::abs(1-(lambda / lambda1)) > 0.001){
        lambda1 = lambda;
        lambda -= func(lambda)/ableitung(lambda, std::bind(func, std::placeholders::_1));
        // test ob lambda nan
        if (lambda != lambda) return -1;
    }
    return lambda;
}