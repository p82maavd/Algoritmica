
#include <iostream>
#include <vector>
#include <fstream>
//#include <tuple>
#include <algorithm>    
#include <map>

using namespace std;

struct Material{
  string id;
  int volumen;
  float precio;
};

map<int,float> calculoMateriales(const std::vector<std::vector<int>> &resultado, const std::vector<Material> &materiales){

    int j=resultado[0].size()-1, i=resultado.size()-1;
    map<int,float> materialesUsados;
    int volumen=0;
    while(i != 0 && j!=0 && volumen<resultado[0].size()-1){

        if( resultado[i][j]==resultado[i-1][j]){
            i=i-1;

        }
        
        else if((int)resultado[i][j]==resultado[i-1][j-materiales[i].volumen]+(int)(materiales[i].precio*materiales[i].volumen)){
            
            materialesUsados.insert(std::pair<int,float>(materiales[i].volumen,materiales[i].precio));
            //cout << opciones[i];
            volumen+=materiales[i].volumen;
            i-=1;
            j=j-materiales[i].volumen;
        }

        else{
            return materialesUsados;
        }

    }

    return materialesUsados;
}

void mochila(){
    int volumen;
    cout << "Introduce el volumen de la mochila: ";
    cin >> volumen;

    ifstream file("materialesmochila.txt");
    string line;
    vector<Material> materiales; //1. Material2. Volumen 3. Precio
    
    while (getline (file, line)) {
        struct Material material1={line.substr(0,line.find(" ")),stoi(line.substr(line.find(" "),line.find_last_of(" "))), stof(line.substr(line.find_last_of(" ")))};
        materiales.push_back(material1);
    }

    std::vector<int> row(volumen+1);
    std::vector<std::vector<int> > resultado(materiales.size(),row);

    for (int i = 1; i < row.size(); ++i)
    {
        resultado[0][i]=0;
    }

    for (int i = 0; i < materiales.size(); ++i)
    {
        resultado[i][0]=0;
    }
  
    for (int i = 0; i < materiales.size(); i++){
    
        for(int j=0; j< row.size();j++){ 
            if  (j < materiales[i].volumen){

                if(i-1>=0){
               
                
                    resultado[i][j]=resultado[i-1][j];
                }
            }
            else{

                if(i-1>=0){
                    if(resultado[i-1][j]>materiales[i].precio*materiales[i].volumen + resultado[i-1][j-materiales[i].volumen]){
                        resultado[i][j]=resultado[i-1][j];
                    }
                    else{
                        resultado[i][j]= materiales[i].precio*materiales[i].volumen + resultado[i-1][j-materiales[i].volumen];
                    }
                }

                else{

                    if(resultado[i][j]>materiales[i].precio*materiales[i].volumen ){
                        resultado[i][j]=resultado[i][j];
                    }
                    else{
                        resultado[i][j]= materiales[i].precio*materiales[i].volumen;
                    }

                }
                

            }
        }
    }

    /*for(int a=0; a<resultado.size(); a++){
        for (int i = 0; i < resultado[a].size(); ++i)
        {
            cout << resultado[a][i]<<" ";
        }
        cout <<endl;
    }*/


    auto materialesmochila=calculoMateriales(resultado,materiales);

    double cont=0;
    cout <<endl;
    for(map<int,float>::reverse_iterator it = materialesmochila.rbegin(); it != materialesmochila.rend(); ++it){
        std::cout << "Material usado con Volumen: "<<it->first<< " y Precio: " << (double)it->second <<  "\n";
        cont+=it->first*(double)it->second;
        
    }

    cout << endl <<"Numero de materiales empleados: "<< materialesmochila.size() <<endl;
    cout << endl <<"Precio de la mochila: "<< cont <<endl;



}

