
#include <iostream>
#include <vector>
#include <fstream>
//#include <tuple>
#include <algorithm>    

using namespace std;

struct Material{
  string id;
  int volumen;
  int precio;
  string usado;
};

void mochila(){
    int volumen;
    cout << "Introduce el volumen de la mochila: ";
    cin >> volumen;

    ifstream file("materialesmochila.txt");
    string line;
    vector<Material> materiales; //1. Material2. Volumen 3. Precio
    
    while (getline (file, line)) {
        struct Material material1={line.substr(0,line.find(" ")),stoi(line.substr(line.find(" "),line.find_last_of(" "))), stoi(line.substr(line.find_last_of(" "))), "nada"};
        materiales.push_back(material1);
    }

    int resto=volumen;
    int precio=0;
    bool materialDisponible=false;
    
    while(resto!=0 || materialDisponible==true){
        int precioMaximo=0;
        int materialMaximo=0;
        bool materialDisponible=false;

        for(int i=0; i< materiales.size();i++){
            if(materiales[i].usado=="nada"){
                materialDisponible=true;
                if(materiales[i].precio>precioMaximo){
                    precioMaximo=materiales[i].precio;
                    materialMaximo=i;
                }
            }
        }

        if(materialDisponible==true){
            if(resto>=materiales[materialMaximo].volumen){
                materiales[materialMaximo].usado="total";
                resto-=materiales[materialMaximo].volumen;
                cout<< "Almacenamos "<< materiales[materialMaximo].volumen << " del elemento "<<materiales[materialMaximo].id<<endl;
                precio+=materiales[materialMaximo].volumen*materiales[materialMaximo].precio;
            }
            else{
                materiales[materialMaximo].usado="parcial";
                cout<< "Almacenamos "<< resto<< " del elemento "<<materiales[materialMaximo].id<<". Nos sobra "<<materiales[materialMaximo].volumen-resto << " de este material";
                precio+=resto*materiales[materialMaximo].precio;
                resto=0;
            }
        }

        else{
            cout << "Ya no hay mas materiales disponibles"<<endl;
            break;
        }

    }

    cout << endl;
    cout << "Valor en la mochila: "<<precio<<endl;
}
