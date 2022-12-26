
#include <iostream>
#include <vector>
#include "ClaseTiempo.cpp"

using namespace std;

bool lugar(int k, std::vector<int> columnas){

    for(int i=1; i<=k-1; i++){
        if(columnas[i]==columnas[k] || abs(columnas[i]-columnas[k])==abs(i-k)){
            return false;
        }
    }

    return  true;

}

void nreinas(){

    int n;
    cout << endl << "Introduce el Tamaño del Tablero: ";
    cin >>n;
    cout << endl;
    vector<vector<int>> resultado;
    std::vector<int> columnas(n+1);
    
    columnas[1]=0;
    int k=1;
    while(k>0){
        columnas[k]=columnas[k] + 1;
        while( (columnas[k] <= n) && lugar(k, columnas)==false){
            columnas[k] = columnas[k] + 1;
        }
        if( columnas[k] <= n){
            if(k == n){
                
                resultado.push_back(columnas);
            }
            else{
                k=k + 1;
                columnas[k]=0;
            }
        }
        else{
            k=k-1;
        }
    }
    int cont=1;
    for(auto a: resultado){
        cout << "Solucion "<<cont<<": ";
        for(int i=1; i<=n;i++){
            cout << a[i] << " ";
        }
        cont++;
        cout << endl;
    }
    cout << endl;

}

void nreinascentral(){
    int n;
    cout << endl << "Introduce el Tamaño del Tablero: ";
    cin >>n;

    vector<vector<int>> resultado;
    std::vector<int> columnas(n+1);
    
    columnas[1]=n/2;
    
    int k=2;
    Clock time;
    time.start();
    while(k>0){
        columnas[k]=columnas[k] + 1;
        if(columnas[k]==n/2){
            continue;
        }
        else{
            while( (columnas[k] <= n) && lugar(k, columnas)==false){
                columnas[k] = columnas[k] + 1;
            }
            if( columnas[k] <= n){
                if(k == n){
                    resultado.push_back(columnas);
                    break;
                }
                else{
                    k=k + 1;
                    columnas[k]=0;
                }
            }
            else{
                k=k-1;
            }
        }
    }
    time.stop();
    for(auto a: resultado){
        cout << "Solucion: ";
        for(int i=1; i<=n;i++){
            cout << a[i] << " ";
        }
        
        cout << "en "<<(double)(time.elapsed()/1000.0) <<" ms"<< endl;
    }
    cout << endl;

}

void nreinaslasvegas(){
    int n;
    cout << endl << "Introduce el Tamaño del Tablero: ";
    cin >>n;
    vector<vector<int>> resultado;
    std::vector<int> columnas(n+1);
    std::vector<int> ok(n+1);
    int columna, contador, cont=1;
    bool notfound=true;
    
    Clock time;
    time.start();
    while(notfound){
    
        for(int k=1; k<=n;k++){

            contador=0;

            for(int j=1; j<=n; j++){

                columnas[k]=j;
                if(lugar(k,columnas)){
                    contador++;
                    ok[contador]=j;

                }
            }

            if(contador==0){
                break;
            }
            
            columna=ok[(rand()%contador)+1];
            columnas[k]=columna;


        }

        if(contador==0){
            cont++;
        }
        else{

            notfound=false;
            
            resultado.push_back(columnas);
            
        }
    }

    time.stop();
    for(auto a: resultado){
        cout << "Solucion: ";
        for(int i=1; i<=n;i++){
            cout << a[i] << " ";
        }
        
        cout << "en "<<(double)(time.elapsed()/1000.0) <<" ms al "<<cont<<"º intento"<< endl;
    }
    cout << endl;

}
