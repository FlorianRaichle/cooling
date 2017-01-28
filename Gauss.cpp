/*
*   Polynomfit mit Gauß-Newton-Verfahren und Gaußscher Elimination
*   https://de.wikipedia.org/wiki/Gau%C3%9F-Newton-Verfahren
*   https://de.wikipedia.org/wiki/Gau%C3%9Fsches_Eliminationsverfahren
*/

#include "header.h"

// x * H = y
double polyfit(int degree, std::vector <double>& x, std::vector <double>& y,  std::vector <double>& a){
    int n = x.size();
    if (degree >= n){
        std::cout << "FEHLER: Zu hoher Grad gewählt" << std::endl;
        return -1;
    }
    // Matrix aus pariellen Ableitungen nach parametern
    std::vector <std::vector <double> > Jacobi (n, std::vector <double>(degree+1));
    // Matrix für L-R-Decomposition
    std::vector <std::vector <double> > G (degree+1, std::vector <double>(degree+1));
    // Vorwärtssubstitution
    std::vector <double> s (degree+1);
    // Rückwärtssubstitution
    std::vector <double> z (degree+1);
    double epsilon = 1;
    
    // Bilden der partiellen Ableitungen
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= degree; j++) {
            Jacobi[i][j] = pow(x[i],j);
        }
    }
    
    // G = Jacobi^T*Jacobi
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= degree; j++) {
            for (int k = 0; k < n; k++){
                G[i][j] += Jacobi[k][i] * Jacobi[k][j];
            }
        }
    }
    
    // L-R-Decomposition
    for (int i = 0; i <= degree; i++){
        // Zeilen der Restmatrix werden durchlaufen
        for (int k = i+1; k <= degree; k++){
            // Berechnung von L
            G[k][i] = G[k][i] / G[i][i];
            // Spalten der Restmatrix werden durchlaufen
            for (int j = i+1; j <= degree; j++){
                // Berechnung von R
                G[k][j] = G[k][j] - G[k][i] * G[i][j];
            }
        }
    }
    
    if(dev){
        for (int i = 0; i <= degree; i++) {
            for (int j = 0; j <= degree; j++) {
                std::cout << G[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    // Iteration für parameter a
    // a = a - G^-1 * Jacobi^T * r
    // G * s = Jacobi^T * r
    // a = a - s
    while (epsilon > 0.0001){
        
        // Vorwärtseinsetzen L*z=D^T*r
        for (int i = 0; i <= degree; i++) {
            z[i] = 0;
            for (int k = 0; k < n; k++){
                z[i] += (f(a,x[k]) - y[k]) * Jacobi[k][i];
            }
            
            for (int j = 0; j < i; j++) {
                if (i == j ) z[i] -= z[j];
                else z[i] -= G[i][j]*z[j];
            }
        }
        
        // Rückwärtseinsetzen R*s=z
        for (int i = degree; i >= 0; i--) {
            s[i] = z[i];
            for (int j = degree; j > i; j--) {
                s[i] -= G[i][j]*s[j];
            }
            s[i] = s[i]/G[i][i];
        }
        // Parameter berechnen
        // a = a - s
        epsilon = 0;
        double a1 = 0;
        for (int i = 0; i <= degree; i++){
            a1 = a[i];
            a[i] -= s[i];
            epsilon += std::abs(a1 - a[i]);
        }
    }
    // Berechne Residuum (optional)
    double r = 0;
    for (int i = 0; i < y.size(); i++) {
        r += (y[i] - f(a, x[i])) * (y[i] - f(a, x[i]));
    }
    if(dev){
        for (int i = 0; i < a.size(); i++) {
            std::cout <<"a" << i <<": " << a[i] << std::endl;
        }
    }
    return r;
}

// polynom
double f(std::vector <double>& a, double x){
    double y = 0;
    for (int i = 0; i < a.size(); i++){
        y += a[i] * pow(x,i);
    }
    return y;
}