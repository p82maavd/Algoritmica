#include "funciones.hpp"
#include <algorithm>


using namespace std;

void quicksort(vector<int> &v, int iz, int de, int n){
	int i= iz;
	int j= de;
	int x= v[(iz+de)/2];
	
	while(i<=j){
		while(v[i]<x){
			i++;
		}
		while(v[j]>x){
			j--;
		}
		if(i<=j){
			int aux=v[i];
			v[i]=v[j];
			v[j]=aux;
			i++;
			j--;
		}
	}

	if(de-iz<n){
		insercion(v,iz,de);
	}

	else{

		if(iz<j)
			quicksort(v,iz,j,n);	
	
		if(i<de)
			quicksort(v,i,de,n);
	}
	
}



void tiemposOrdenacionQuickSort(int nMin, int nMax, int repeticiones, int incremento, vector <double> &tiemposReales, vector <double> &numeroElementos){

	int iteraciones= (nMax-nMin)/incremento;

	for(int i=0; i< iteraciones+1; i++){

		vector<int> v(nMin+i*incremento);
		
		Clock temporizador;
		vector<double> tiempoMedio(0);


		for(int j=0; j< repeticiones; j++){

			rellenarVector(v);
			
			temporizador.start();

			quicksort(v,0,v.size()-1,0);
			
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

void ordenacionQuickSort(){

	int min, max, incremento, iter, rango;

	cout<<"Introduce el valor minimo de elementos del vector: ";
	cin>>min;

	cout<<"Introduce el valor maximo de elementos del vector: ";
	cin>>max;

	cout<<"Introduce el incremento de elementos del vector: ";
	cin>>incremento;

	cout<<"Introduce el numero de iteraciones por cada numero de elementos: ";
	cin>>iter;

	vector<double> tiemposReales(0), numeroElementos(0), a(2);
	tiemposOrdenacionQuickSort(min,max,iter,incremento,tiemposReales,numeroElementos);
	if(numeroElementos.size()==1){
		cout << numeroElementos[0] << " elementos ordenados en " << tiemposReales[0] << " ms"<<endl;
	}
	ajusteLogaritmico(numeroElementos, tiemposReales, a);

	cout<<endl<<"La funcion de la curva es: " << a[0] << " + " << a[1]<<"nlogn "<<endl;

	double size=1.0;
	while(size!=0){
		cout << endl<<"Para que tamaño quieres calcular el tiempo Estimado? ";
		
		cin>>size;
		cout << "El tiempo estimado es "<<calcularTiempoEstimadoLogaritmico(size, a)<< " dias" <<endl;
	}

}

int calculoOptimoQuickSort(){
	int n=10;
	double sumaQuickSort=0.0;
	double sumaInsercion=0.0;
	while(true){
		double sumaQuickSort=0.0;
		double sumaInsercion=0.0;
		for(int i=0; i<100; i++){
			vector<int> v(n);
			vector<int> v2(n);
			
			Clock temporizador, temporizador2;

			rellenarVector(v);
			v2=v;
				
				
			temporizador.start();

			//quicksort(v,0,v.size()-1);
			quicksort(v,0,v.size()-1,v.size()-1);
				
			temporizador.stop();
			sumaQuickSort+=temporizador.elapsed();

			if(estaOrdenado(v)==false){
				cout << "NO ESTA ORDENADO"<<endl;
			}

			int quick=temporizador.elapsed();

			temporizador2.start();
			insercion(v2,0,v2.size()-1);
			temporizador2.stop();
			sumaInsercion+=temporizador2.elapsed();
		}
		//cout<<n <<" Tiempo Quicksort: "<<sumaQuickSort<< " Tiempo Insercion: "<<sumaInsercion<<endl;
		if(sumaQuickSort<sumaInsercion){
			
			return n;
		}
		else{
			n++;
			
		}
	}

}

void tiemposOrdenacionExtraQuickSort(int repeticiones, vector <double> &tiemposReales, vector <double> &numeroElementos){	
		

		vector<int> v(1000000);
		
		for(int j=1000; j>=0; j-=50){

			vector<double> tiempoMedio(0);

			for(int i=0; i< repeticiones; i++){
				Clock temporizador;

				rellenarVector(v);
			
				temporizador.start();

				quicksort(v,0,v.size()-1,j);
				
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


void ordenacionExtraQuickSort(){
	int iter;
	cout<<"Introduce el numero de iteraciones: ";
	cin>>iter;
	
	vector<double> tiemposReales(0), numeroElementos(0);
	tiemposOrdenacionExtraQuickSort(iter, tiemposReales,numeroElementos);
	
}