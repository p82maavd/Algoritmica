
#include "funciones.hpp"
#include <limits>

using namespace std;

void merge(vector<int> u, vector<int> v, vector<int> &t){

	int i = 0;
	int j = 0;
	int k=0;
	//u[u.size()-1]= std::numeric_limits<int>::infinity();
	//v[v.size()-1]= std::numeric_limits<int>::infinity();
	for(k=0;i<u.size() && j<v.size();k++){
		if(u[i] <= v[j]){

			t[k] = u[i];
			i = i + 1;
		}
		else{
			t[k] = v[j];
			j = j + 1;
		}
	}

	while(i<u.size()){
		t[k]=u[i];
		i++;
		k++;
	}

	while(j<v.size()){
		t[k]=v[j];
		j++;
		k++;
	}
}

void fusion(vector<int> &t, int n){

	if(t.size()==1 || t.size()==0){
		return;
	}
	
	if(t.size()<n){
		insercion(t,0,t.size()-1);
	}

	
	else{
		vector<int> u(t.size()/2);
		vector<int> v(t.size() - u.size());
		for(int i=0; i<t.size()/2; i++){
			u[i] = t[i];
		}
	
		for(int i=t.size()/2; i<t.size(); i++){
			v[i-t.size()/2] = t[i];
		}
		fusion(u,n);
		fusion(v,n);
		merge(u, v, t);
	}
}

int calculoOptimoFusion(){
	int n=10;
	double sumaFusion=0.0;
	double sumaInsercion=0.0;
	while(true){
		double sumaFusion=0.0;
		double sumaInsercion=0.0;
		for(int i=0; i<25; i++){
			vector<int> v(n);
			vector<int> v2(n);
			
			Clock temporizador, temporizador2;

			rellenarVector(v);
			v2=v;
				
				
			temporizador.start();

			fusion(v,0);
				
			temporizador.stop();
			sumaFusion+=temporizador.elapsed();

			if(estaOrdenado(v)==false){
				cout << "NO ESTA ORDENADO"<<endl;
			}

			int quick=temporizador.elapsed();

			temporizador2.start();
			insercion(v2,0,v2.size()-1);
			temporizador2.stop();
			sumaInsercion+=temporizador2.elapsed();
		}
		//cout<<n <<" Tiempo Quicksort: "<<sumaFusion<< " Tiempo Insercion: "<<sumaInsercion<<endl;
		if(sumaFusion<sumaInsercion){
			
			return n;
		}
		else{
			n++;
			
		}
	}

}

void tiemposOrdenacionFusion(int nMin, int nMax, int repeticiones, int incremento, vector <double> &tiemposReales, vector <double> &numeroElementos){

	int iteraciones= (nMax-nMin)/incremento;


	for(int i=0; i< iteraciones+1; i++){

		vector<int> v(nMin+i*incremento);
		Clock temporizador;
		vector<double> tiempoMedio(0);


		for(int j=0; j< repeticiones; j++){

			rellenarVector(v);
			
			temporizador.start();

			fusion(v,0);
			
			temporizador.stop();

			if(estaOrdenado(v)==false){
				cout << "NO ESTA ORDENADO"<<endl;
			}
	
			tiempoMedio.push_back(temporizador.elapsed()/1000);
			
		}
		double suma=0;
	
		for(int k=0;k<tiempoMedio.size();k++){
			suma+=tiempoMedio[k];
		}
		

		tiemposReales.push_back(suma/(double)repeticiones);
		numeroElementos.push_back(nMin+i*incremento);
	}

}



void ordenacionFusion(){
	int min, max, incremento, iter;

	cout<<"Introduce el valor minimo de elementos del vector: ";
	cin>>min;

	cout<<"Introduce el valor maximo de elementos del vector: ";
	cin>>max;

	cout<<"Introduce el incremento de elementos del vector: ";
	cin>>incremento;

	cout<<"Introduce el numero de iteraciones por cada numero de elementos: ";
	cin>>iter;
	vector<double> tiemposReales(0), numeroElementos(0), a(2);
	tiemposOrdenacionFusion(min,max,iter,incremento,tiemposReales,numeroElementos);
	if(numeroElementos.size()==1){
		cout << numeroElementos[0] << " elementos ordenados en " << tiemposReales[0] << " ms"<<endl;
	}
	ajusteLogaritmico(numeroElementos,tiemposReales,a);
	
	cout<<endl<<"La funcion de la curva es: " << a[0] << " + " << a[1]<<"*nlogn "<<endl;
	double tiempo=0.0;
	double size=1.0;
	while(size!=0){
		cout << endl<<"Para que tamaño quieres calcular el tiempo Estimado? ";
		
		cin>>size;
		tiempo=calcularTiempoEstimadoLogaritmico(size, a);
		cout << "El tiempo estimado es "<<tiempo<< " dias" <<endl;
	}



}

void tiemposOrdenacionExtraFusion(int repeticiones, vector <double> &tiemposReales, vector <double> &numeroElementos){	

		vector<int> v(1000000);
		
		for(int j=1000; j>=0; j-=50){

			vector<double> tiempoMedio(0);

			for(int i=0; i< repeticiones; i++){
				Clock temporizador;

				rellenarVector(v);
			
				temporizador.start();

				fusion(v,j);
				
				temporizador.stop();

				if(estaOrdenado(v)==false){
					cout << "NO ESTA ORDENADO"<<endl;
				}
		
				tiempoMedio.push_back(temporizador.elapsed()/1000);
				
			}
			double suma=0;
		
			for(int k=0;k<tiempoMedio.size();k++){
				suma+=tiempoMedio[k];
			}

			
			tiemposReales.push_back(suma/repeticiones);
			numeroElementos.push_back(j);			
			
		}

		ofstream tiempos("datosFinales.txt");
		for(int i=0; i<tiemposReales.size(); i++){
			tiempos << numeroElementos[i] <<  " " << tiemposReales[i]<<endl;
		}
		tiempos.close();
	
}


void ordenacionExtraFusion(){
	
	int iter;

	cout<<"Introduce el numero de iteraciones: ";
	cin>>iter;

	vector<double> tiemposReales(0), numeroElementos(0);
	tiemposOrdenacionExtraFusion(iter, tiemposReales,numeroElementos);
	
}