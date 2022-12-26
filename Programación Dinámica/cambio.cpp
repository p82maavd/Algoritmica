
#include <iostream>
#include <vector>
#include <fstream>
#include <map>


using namespace std;


int minimo (int a, int b){
	if(a>b){
		return b;
	}
	return a;
}

map<int,int> calculoMonedas(const std::vector<std::vector<int>> &resultado, const std::vector<int> &opciones){

	int j=resultado[0].size()-1, i=resultado.size()-1;
    map<int,int> monedas;
    while(i != 0 && j!=0){

    	if(i-1>=0 && resultado[i][j]==resultado[i-1][j]){
    		i=i-1;

    	}
    	else if(j-opciones[i]>=0){
    		
    		auto ret =monedas.insert(std::pair<int,int>(opciones[i],1));
            if (ret.second==false) {
                ret.first->second++;
            }
            
    		j=j-opciones[i];
    	}

    }

    return monedas;
}

void cambio(){

    int a,n,cont=0;
    cout  <<"Introduce el cambio en centimos: ";
    cin>>n;
    ifstream file("sistemamonetario.txt");
    string line;
    vector<int> opciones(0);
    while (getline (file, line)) {
        a=stoi(line);
        opciones.push_back(a);
        
    }
    std::vector<int> row(n+1);
    std::vector<std::vector<int> > resultado(opciones.size(),row);

    for(int i=0;i<opciones.size();i++){
    	resultado[i][0]=0;
    }
    

    for(int i=0;i<opciones.size();i++){
    	for(int j=1;j<=n;j++){
    		if(i==0 && j<opciones[i]){

    			resultado[i][j]=99999;
    		}
    		else{
    			if(i==0){
    				resultado[i][j]=1+resultado[i][j-opciones[0]];
    			}
    			else{
    				if(j<opciones[i]){
    					resultado[i][j]=resultado[i-1][j];
    				}
    				else{
    					resultado[i][j]=minimo(resultado[i-1][j],1+resultado[i][j-opciones[i]]);
    				}
    			}
    		}
    	}
    }

    //Tabla Resultante
    for(int a=0; a<resultado.size(); a++){
    	for (int i = 0; i < resultado[a].size(); ++i)
    	{
    		cout << resultado[a][i]<<" ";
    	}
    	cout <<endl;
    }

    auto monedas=calculoMonedas(resultado,opciones);
    
    for(map<int,int>::reverse_iterator it = monedas.rbegin(); it != monedas.rend(); ++it){
        std::cout << (double)it->first/100 << "€ " << it->second <<  "\n";
        cont+=it->second;
    }

    cout << endl <<"Numero de monedas empleadas: "<< cont <<endl;

}


