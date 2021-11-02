
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

int maximo(vector<int> &opciones, int s, int n){
    
    for(auto x: opciones){
        if(s+x<=n){
            return x;
        }
    }
    return 0;
}

void cambio(){

    int n;
    ifstream file("SistemaMonetario.txt");
    string line;
    while (getline (file, line)) {
        n=stoi(line);
        
    }

    vector<int> opciones={50000,20000,10000,5000,2000,1000,500,200,100,50,20,10,5,2,1};
    unordered_map<int,int> S;
    
    int s=0;
    while(s!=n){
        int x=maximo(opciones,s,n);
        if(x!=0){
            
            auto ret =S.insert(std::pair<int,int>(x,1));
            if (ret.second==false) {
                ret.first->second++;
            }
            s=s+x;
        }
        else{
            cout<<"Solucion no encontrada";
            return;
        }

    }
    cout<<endl;
    for(auto it = S.begin(); it != S.end(); ++it){
        std::cout << (double)it->first/100 << "€ " << it->second <<  "\n";
    }

    return;

}


/*void cambio2(){

    int cantidad;

    cout<<"Introduce la cantidad en centimos: ";
    cin>>cantidad;
    
    vector<int> opciones={50000,20000,10000,5000,2000,1000,500,200,100,50,20,10,5,2,1};
    vector<int> resultado(opciones.size());
    
    int cont=0;
    while(cantidad!=0){
        
        if(cantidad>=opciones[cont]){
            resultado[cont]=cantidad/opciones[cont];
            cantidad=cantidad%opciones[cont];
        }
        cont++;

    }
    cout << endl;
    for(auto a:resultado){
        cout << a<< " ";
    }
    cout<<endl;

}*/
