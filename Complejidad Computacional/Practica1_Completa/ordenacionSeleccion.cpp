#include "funciones.hpp"


using namespace std;

void rellenarVector(vector<int> v){

	for(int i =0 ; i< v.size();i++){

		v[i]= rand()%10000000;

	}
}

bool seleccion(vector<int> v){


	int posicionmenor, aux;
	for(int i=0; i<v.size();i++){
		posicionmenor=i;

		for(int j=i+1; j< v.size();j++){

			if(v[j]<v[posicionmenor]){
				posicionmenor=j;
			}
		}

		aux=v[i];
		v[i]=v[posicionmenor];
		v[posicionmenor]=aux;
	}
	return true;

}

bool estaOrdenado(vector<int> v){

	for(int i=0; i<v.size()-1;i++){

		if(v[i]>v[i+1]){
			return false;
		}
	}

	return true;
}

void tiemposOrdenacionSeleccion(int nMin, int nMax, int repeticiones, int incremento, vector <double> &tiemposReales, vector <double> &numeroElementos){

	int iteraciones= (nMax-nMin)/incremento;


	for(int i=0; i< iteraciones+1; i++){

		vector<int> v(nMin+i*incremento);
		Clock temporizador;
		vector<double> tiempoMedio(0);


		for(int j=0; j< repeticiones; j++){

			rellenarVector(v);
			
			
			temporizador.start();

			seleccion(v);
			
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



void ordenacionSeleccion(){

	int min, max, incremento, iter;

	cout<<"Introduce el valor minimo de elementos del vector: ";
	cin>>min;

	cout<<"Introduce el valor maximo de elementos del vector: ";
	cin>>max;

	cout<<"Introduce el incremento de elementos del vector: ";
	cin>>incremento;

	cout<<"Introduce el numero de iteraciones por cada numero de elementos: ";
	cin>>iter;
	vector<double> tiemposReales(0), numeroElementos(0), a(3);
	tiemposOrdenacionSeleccion(min,max,iter,incremento,tiemposReales,numeroElementos);
	ajustePolinomico(numeroElementos, tiemposReales, a);

	cout<<endl<<"La funcion de la curva es: " << a[0] << " + " << a[1]<<"n + "<<a[2]<<"n^2"<<endl;

	double size=1.0;
	while(size!=0){
		cout << endl<<"Para que tamaño quieres calcular el tiempo Estimado? ";
		
		cin>>size;
		cout << "El tiempo estimado es "<<calcularTiempoEstimadoPolinomico(size, a)<< " dias" <<endl;
	}
	

}