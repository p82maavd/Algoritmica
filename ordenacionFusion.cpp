
#include "funciones.hpp"

using namespace std;
 
void merge(vector<int> v, int l, int m, int r) {
  int i = l;
  int j = m + 1;
  int k = l;

  /* create temp vay */
  int temp[v.size()];

  while (i <= m && j <= r) {
    if (v[i] <= v[j]) {
      temp[k] = v[i];
      i++;
      k++;
    } else {
      temp[k] = v[j];
      j++;
      k++;
    }

  }

  /* Copy the remaining elements of first half, if there are any */
  while (i <= m) {
    temp[k] = v[i];
    i++;
    k++;

  }

  /* Copy the remaining elements of second half, if there are any */
  while (j <= r) {
    temp[k] = v[j];
    j++;
    k++;
  }

  /* Copy the temp vay to original vay */
  for (int p = l; p <= r; p++) {
    v[p] = temp[p];
  }
}

/* l is for left index and r is right index of the 
   sub-vay of v to be sorted */
void fusion(vector<int> v, int l, int r) {
  if (l < r) {
    // find midpoint
    int m = (l + r) / 2;

    // recurcive mergesort first and second halves 
    fusion(v, l, m);
    fusion(v, m + 1, r);

    // merge
    merge(v, l, m, r);
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

			fusion(v,0,v.size()-1);
			
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