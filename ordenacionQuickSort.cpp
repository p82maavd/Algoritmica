#include "funciones.hpp"


using namespace std;


void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (vector<int> v, int low, int high)
{
    int pivot = v[high];    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (v[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&v[i], &v[j]);
        }
    }
    swap(&v[i + 1], &v[high]);
    return (i + 1);
}
 

 

void quicksort(vector<int> v, int low, int high, int n){


	 if (low < high){
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(v, low, high);
 
        // Separately sort elements before
        // partition and after partition
		if(high-low<n){
			insercion(v);
		}
		else{
        	quicksort(v, low, pi - 1,n);
        	quicksort(v, pi + 1, high,n);
		}
    }

}

void tiemposOrdenacionQuickSort(int nMin, int n, int nMax, int repeticiones, int incremento, vector <double> &tiemposReales, vector <double> &numeroElementos){

	int iteraciones= (nMax-nMin)/incremento;

	for(int i=0; i< iteraciones+1; i++){

		vector<int> v(nMin+i*incremento);
		Clock temporizador;
		vector<double> tiempoMedio(0);


		for(int j=0; j< repeticiones; j++){

			rellenarVector(v);
			
			
			temporizador.start();

			quicksort(v,0,v.size()-1,n);
			
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

	cout<<"Introduce el tamaño maximo del vector para ordenarlo por QuickSort: ";
	cin>>rango;

	vector<double> tiemposReales(0), numeroElementos(0), a(2);
	tiemposOrdenacionQuickSort(min,rango,max,iter,incremento,tiemposReales,numeroElementos);
	ajusteLogaritmico(numeroElementos, tiemposReales, a);

	cout<<endl<<"La funcion de la curva es: " << a[0] << " + " << a[1]<<"nlogn "<<endl;

	double size=1.0;
	while(size!=0){
		cout << endl<<"Para que tamaño quieres calcular el tiempo Estimado? ";
		
		cin>>size;
		cout << "El tiempo estimado es "<<calcularTiempoEstimadoLogaritmico(size, a)<< " dias" <<endl;
	}
	

}