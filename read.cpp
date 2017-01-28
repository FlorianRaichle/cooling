/*
*   Einlesen aus Textdateien
*/

#include "header.h"
#include <sstream>

int read_file(std::string name, tabelle& Daten){
    char delim = '\t';
    std::string line;
    std::ifstream file(name);
    if(file.is_open()){
      int r = 0;
      
      // discard first row
      file.ignore(256,'\n');
      
      // get lines in file
      while (getline(file, line)){
        Daten.push_back(std::vector <double>());
        
        // tokenize with space as delimiter
        std::istringstream ss(line);
        //discard first column
        ss.ignore(256, delim);
        std::string x;
        while (ss >> x){
            Daten[r].push_back(stod(x));
        }
        r++;
      }
      file.close();
      
      // print array to screen
      if(dev){
        std::cout << name <<": " << std::endl;
        for (int i = 0; i < Daten.size(); i++) {
          for (int j = 0; j < Daten[i].size(); j++){
            std::cout << Daten[i][j] << " ";
          }
          std::cout << std::endl;
        }
      }
      return 0;
    }
    else{
        std::cout << "could not read file " << name << std::endl;
        return 1;
    }
}