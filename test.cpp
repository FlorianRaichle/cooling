#include "header.h"

void test_Gauss(){
    int degree;
    std::cout << "enter degree ";
    std::cin >> degree;
    std::vector <double> y = {156176.54,127153.19,115140.77,114033.92,109975,97619.4,100649,102224};
    std::vector <double> p = {15,20,25,30,35,40,45,50};
    std::vector <double> a (degree+1,1);
    polyfit(degree, p ,y, a);
}

void test_read(){
    tabelle arr;
    std::cout << "testing read" << std::endl;
    read_file("rohre.txt", arr);
}

void test_durchmesser(){
    std::vector <std::vector <double> > d;
    std::vector <double> Leistung = {208,152,113,227,137,238,178,104,191};
    std::vector <double> Laenge = {25, 57, 58, 59, 60, 61};
    std::vector <double> V = {10, 11, 12, 13, 14, 15};
    std::vector <double> Delta_p_einbaute = {1, 2, 3, 4, 5, 6};
    double Lambda = 2;
    double Dichte = 1;
    double V_ges = 1;
    // Bsp Zugriff Laenge[0], hier Bspzahlen eingefügt
    for (int i=0; i < Leistung.size(); i++) { // gibt Dimension in x-Richtung dieser Tabelle an
        d.push_back(std::vector <double>());
        for (int j=0; j < Laenge.size(); j++) {
            
            d[i].push_back(durchmesser (Leistung[i], Dichte, Delta_p_einbaute[j], V_ges, V[j], Laenge[j], Lambda));
            std::cout << d[i][j] << " ";
            
        }
        std::cout << std::endl;
    }
}

void test_ausgabe()
{
    ergebnisse Ergebnis;
    Ergebnis.daten={{1,2,3},{1,2,3}};
   
    ergebnisse Ergebnis2;
    Ergebnis2.daten={{1,2,3},{1,2,3}};
    
    ausgabe("test.txt", Ergebnis,false);
    
   
}
/*
void test_newt(){
    std:: cout << newt(20000,0.1,60,25000,1000,0.001,0.0004,0.5);
}*/
void test_newt(){
    //durchmesser(Leistung, Dichte, Delta_p_einbaute, V_ges, V, Laenge, lambda)
    double Leistung = 20000;
    double V = 0.1;
    double Laenge = 60;
    double dp = 25000;
    double Dichte = 1000;
    double Visc = 0.001;
    double k = 0.0004;
    double v_ges = 0.5;
    std:: cout <<"lambda " << newton(0.02, std::bind(colebrook,std::placeholders::_1,Dichte, Visc, k, V, std::bind(durchmesser, Leistung, Dichte, dp, v_ges, V, Laenge, std::placeholders::_1)));
}
double poly (std::vector <double>& array, double x);
void test_func(){
    std::vector <double> a = {280279,-12203.3,283.562,-2.22876};

    std::cout << poly(a,77.525);
}
void test(){
    // D (0.02, 105, 431, 900, 50, 30, 0.2)
    std::cout << durchmesser (30, 900, 0.2, 431, 105, 50, 0.01) << std::endl;
    // double lambda, double Dichte, double Visc, double k, double V, double D
    std::cout << colebrook(0.0345, 1000, 0.001, 0.4, 60, 0.152);
    //std::cout << Ventileinstellungen()
}