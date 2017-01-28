/*
*   Ausgabe der Ergebnisse in eine Textdatei
*/
#include "header.h"
#include <iomanip>
using namespace std;

void ausgabe(string Name, ergebnisse& Ergebnis, bool append)
{
    ofstream fileout;
    if(append){
        fileout.open("ergebnisse/"+Name, ofstream::app);
        fileout << endl;
    }else{
        fileout.open("ergebnisse/"+Name);
    }
    fileout << Ergebnis.titel << endl;
    if (Ergebnis.zeilen.size() > 0) fileout << setw(10) << "\t";
    for (int i = 0; i < Ergebnis.spalten.size(); i++) {
        fileout << setw(10) << left << Ergebnis.spalten[i] << "\t";
    }
    fileout << endl;
    for (int i=0; i < Ergebnis.daten.size(); i++)
    {
        if(Ergebnis.zeilen.size() > i) fileout << setw(10) << Ergebnis.zeilen[i] << "\t";
        for (int u = 0; u < Ergebnis.daten[i].size(); u++)
        {
            fileout << setw(10) << left << Ergebnis.daten[i][u] << "\t";
        }
        fileout << endl;
    }
    fileout.close();    
}