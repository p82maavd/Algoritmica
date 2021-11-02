
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <algorithm>


using namespace std;

struct Material
{
  int volumen;
  int precio;
  string usado;
};

void mochila(){
    int volumen;
    cout << "Introduce el volumen de la mochila: ";
    cin >> volumen;

    ifstream file("mochila.txt");
    string line;
    vector<Material> materiales; //1. Material2. Volumen 3. Precio
    
    while (getline (file, line)) {
        struct Material material1={stoi(line.substr(line.find(" "),line.find_last_of(" "))), stoi(line.substr(line.find_last_of(" "))), "nada"};
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
                cout<< "Almacenamos "<< materiales[materialMaximo].volumen << " del elemento "<<materialMaximo+1<<endl;
                precio+=materiales[materialMaximo].volumen*materiales[materialMaximo].precio;
            }
            else{
                materiales[materialMaximo].usado="parcial";
                cout<< "Almacenamos "<< resto<< " del elemento "<<materialMaximo+1;
                precio+=resto*materiales[materialMaximo].precio;
                resto=0;
            }
        }

    }

    cout << endl;
    cout << "Valor en la mochila: "<<precio<<endl;
}

/*void mochila2(){
    int volumen;
    cout << "Introduce el volumen de la mochila: ";
    cin >> volumen;

    ifstream file("mochila.txt");
    string line;
    vector<tuple<string,int,int>> materiales; //1. Material2. Volumen 3. Precio
    while (getline (file, line)) {
    
        materiales.push_back(make_tuple(line.substr(0,line.find(" ")),  stoi(line.substr(line.find(" "),line.find_last_of(" "))), stoi(line.substr(line.find_last_of(" "))))); 
    }

    std::sort(materiales.begin(), materiales.end(), [](tuple<string,int,int> a, tuple<string,int,int> b) {
        return get<2>(a) > get<2>(b);
    });

    for(auto a: materiales){
        cout << "Material: "<< get<0>(a) <<" Volumen: " << get<1>(a) << " Precio: "<< get<2>(a) << endl;
    }
    int s=volumen;
    int p=0;
    

    for(int i=0; i< materiales.size() && s >0; i++){
            
        if(s-get<1>(materiales[i])>=0){ 
            s-=get<1>(materiales[i]);
            cout << "Almacenamos "<<get<1>(materiales[i])<<" de "<<get<0>(materiales[i])<<endl;
            p+=get<2>(materiales[i])*get<1>(materiales[i]);
        }
        else{
            cout << "Almacenamos "<<s<<" de "<<get<0>(materiales[i])<<endl;
            p+=get<2>(materiales[i])*s;
            s=0;    
        }
    }
    cout << endl;
    cout << "Valor en la mochila: "<<p<<endl;

}*/
