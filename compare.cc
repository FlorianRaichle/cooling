/*
*   Auswahl der Rohre und Druckverlust
*/
#include"header.h"

using namespace std;

double Vergleich (tabelle& lief_Rohre, ergebnisse& durchmesser){
    for (int i = 0; i <durchmesser.size(); i++){
        for (int j = 0; j < durchmesser.daten[i].size(); j++){
            
            if (durchmesser.daten[i][j] < lief_Rohre[0][0] || durchmesser.daten[i][j] > lief_Rohre[lief_Rohre.size][0]){
                durchmesser.daten[i][0] = 0;
            }
            //Liegt der Durchmesser nicht im Bereich lieferbarer Rohre wird null aussgegeben
            /*if (durchmesser.daten[i][j] == lief_Rohre[0][0]){
                durchmesser.daten[i][0]=lief_Rohre[0][0];
            }*/
            //Ist der berechnete Durchmesser gleich einem lieferbaren Rohr so wird das jeweilige Rohr ausgegeben
            
            for(int k=1; k <= 7; k++){
                if(durchmesser.daten[i][j] <= lief_Rohre[k][0] && durchmesser.daten[i][j] > lief_Rohre[k-1][0]){
                    durchmesser.daten[i][j]=lief_Rohre[k][0];
                } 
                //Liegt der berechnete Durchmesser zwischen den Durchmessern zweier lieferbarer Rohre so wird der nächst größere gewählt
            }
        }
    }
}

<<endl<<endl<<"Innendurchmesser:"<<endl<<endl;
for (int i=0; i<lief_Rohre.size(); i++){
        cout<<endl;
    for (int j = 0; j < Rohre.size(); j++){
            cout<<durchmesser.daten[i][j]<<setw(10);}
    
}
   
// Berechne Ventileinstellungen


double Ventileinstellungen (ergebnisse Ventile, ergebnisse Durchmesser, tabelle Pumpen, tabelle Stoffdaten, tabelle double V_ges){
    double delta_p_Ventil[n][m];
    double Reynolds, delta_p_Verbraucher, Lamda, delta_p_Reibung;
    
    for (int i=0; i < lief_Rohre.size(); i++){
        if(d[i][0] == 0){
            for (int j = 0; j<lief_Rohre.size(); j++){
                delta_p_Ventil[i][j]=0;
            }
        }else{
            Leistung_Mechanisch = Pumpen [0][p];
            delta_p_gesamt = Leistung_Mechanisch / V_ges;
        }
            
        for (int j = 0; j < Rohre.size(); j++){
        
            d_Verbraucher = d[i][j];
            k = Rohre[3][j];
            Laenge = Rohre[2][j];
            delta_p_Verbraucher = Rohre[1][j];
            V = Daten.Rohre[0][j];
            
            Reynolds = 4*Dichte*V/(Visc*M_PI*d_Verbraucher); 
            //Berechnung Reynolds_real
            
            Widerstandszahl = newt(colebrook, durchmesser_Verbraucher, Reynolds, k); 
            //Berechnung reales Lambda mit Newtonverfahren
            
            delta_p_Reibung = Lambda*Laenge*Dichte*8*V*V/(pow(d_Verbraucher, 5)*M_PI*M_PI);
            //Berechnung der durch Reibung verursachten Druckverluste
            
            delta_p_Ventil [i][j]=delta_p_gesamt-delta_p_Verbraucher-delta_p_Reibung; 
            //Berechung des von dem Ventil zu erzeugenden Druckverlust
            
            cout<<endl<<endl<<"Ventileinstellungen:"<<endl<<endl;
            for (int i=0; i<lief_Rohre.size(); i++){
                cout<<endl;
                for (int j=0; j<lief_Rohre.size(); j++){
                    cout<<"delta_p_Ventil[i][j]:"<<setw(10);
                    //Ausgabe der Ventileinstellung für jede Leitung
                }
            }
        }
    }
}
