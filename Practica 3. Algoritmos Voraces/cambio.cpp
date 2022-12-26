
#include <iostream>
#include <vector>
#include <fstream>
#include <map>


using namespace std;

int maximo(vector<int> &opciones, int s, int n){
    
    for(int x=0; x<opciones.size();x++){
        if(s+opciones[x]<=n){
            return opciones[x];
        }
    }
    return 0;
}

void cambio(){

    int a,n;
    cout  <<"Introduce el cambio en centimos: ";
    cin>>n;
    ifstream file("sistemamonetario.txt");
    string line;
    vector<int> opciones(0);
    while (getline (file, line)) {
        a=stoi(line);
        opciones.push_back(a);
        
    }

    map<int,int> S;
    
    int s=0;
    while(s!=n){
        
        auto x=maximo(opciones,s,n);
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
    int cont=0;
    for(map<int,int>::reverse_iterator it = S.rbegin(); it != S.rend(); ++it){
        std::cout << (double)it->first/100 << "€ " << it->second <<  "\n";
        cont+=it->second;
    }

    cout << endl <<"Numero de monedas empleadas: "<< cont <<endl;

    return;

}
