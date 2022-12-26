
#include "funciones.hpp"

using namespace std;

int fibonacci(int num){

	if(num == 0 || num==1)
        return num;
    else
        return fibonacci(num-1) + fibonacci(num-2);
}


void tiemposFibonacciRecursivo(int nMin, int nMax, int incremento, vector <double> &tiemposReales, vector <double> &numeroElementos){

	int iteraciones= (nMax-nMin)/incremento;


	for(int i=0; i< iteraciones+1; i++){

		Clock temporizador;
		
						
		temporizador.start();

		fibonacci(nMin+i*incremento);
			
		temporizador.stop();
	
		tiemposReales.push_back(temporizador.elapsed()/1000);
		numeroElementos.push_back(nMin+i*incremento);
			
	}

}

void fibonacciRecursivo(){
	int min, max, incremento;
	

	cout<<"Introduce el valor minimo del termino a calcular: ";
	cin>>min;

	cout<<"Introduce el valor maximo del termino a calcular: ";
	cin>>max;
	cout<<"Introduce el incremento: ";
	cin>>incremento;
	vector<double> tiemposReales(0), numeroElementos(0), a(2);
	tiemposFibonacciRecursivo(min,max,incremento,tiemposReales,numeroElementos);
	ajusteExponencial(numeroElementos,tiemposReales,a);
	
	cout<<endl<<"La funcion de la curva es: " << a[0] << " + " << a[1]<<"*2^n "<<endl;
	double tiempo=0.0;
	double size=1.0;
	while(size!=0){
		cout << endl<<"Para que tamaño quieres calcular el tiempo Estimado? ";
		
		cin>>size;
		tiempo=calcularTiempoEstimadoExponencial(size, a);
		cout << "El tiempo estimado es "<<tiempo<< " dias" <<endl;
	}



}