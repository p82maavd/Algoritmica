#include "funciones.hpp"

using namespace std;

void rellenarMatriz(vector < vector < double > > &A){
	double x =0.0;
	for(int i = 0; i <A[0].size(); i++){
		for(int j = 0; j < A[0].size(); j++){
			x=(double)(rand()%11)/10.0;
			A[i][j]=1.05-x;
		}
	}
}


void multiplicarMatrices2(const vector < vector < double > > &m1, const vector < vector < double > > &m2, vector < vector < double > > &producto)
{

	for(unsigned int i = 0; i < m1.size(); i++) //Recorre filas de la primera matriz
	{
		for(unsigned int j = 0; j < m2[0].size(); j++) //Recorre columnas de la segunda matriz
		{
			producto[i][j] = 0.0;
			for(unsigned int k = 0; k < m1[0].size(); k++) //Recorre los elementos a multiplicar (numero de columnas de la primera matriz)
				producto[i][j] = producto [i][j] + m1[i][k]*m2[k][j];
		}
	}
}


void tiemposMatricesCuadradas(int nMin, int nMax, int incremento, vector <double> &tiemposReales, vector <double> &numeroElementos){

	int iteraciones= (nMax-nMin)/incremento;


	for(int i=0; i< iteraciones+1; i++){

		Clock temporizador;
		vector<vector<double> > A(nMin+i*incremento, vector<double>(nMin+i*incremento,0));
		vector<vector<double> > B(nMin+i*incremento, vector<double>(nMin+i*incremento,0));
		vector<vector<double> > X(nMin+i*incremento, vector<double>(nMin+i*incremento,0));

		rellenarMatriz(A);
		rellenarMatriz(B);
						
		temporizador.start();

		multiplicarMatrices2(A,B,X);
			
		temporizador.stop();
	
		tiemposReales.push_back(temporizador.elapsed()/1000);
		numeroElementos.push_back(nMin+i*incremento);
			
	}

}




void productoMatricesCuadradas(){
	

	int min, max, incremento;
	

	cout<<"Introduce el valor minimo de orden de la matriz: ";
	cin>>min;

	cout<<"Introduce el valor maximo de orden de la matriz: ";
	cin>>max;
	cout<<"Introduce el incremento: ";
	cin>>incremento;

	vector<double> tiemposReales(0), numeroElementos(0), a(4);
	tiemposMatricesCuadradas(min,max,incremento,tiemposReales,numeroElementos);
	ajustePolinomico(numeroElementos, tiemposReales, a);

	cout<<endl<<"La funcion de la curva es: " << a[0] << " + " << a[1]<<"n + "<<a[2]<<"n^2 + "<<a[3]<<" n^3"<<endl;
	double tiempo=0.0;
	double size=1.0;
	while(size!=0){
		cout << endl<<"Para que tamaño quieres calcular el tiempo Estimado? ";
		
		cin>>size;
		tiempo=calcularTiempoEstimadoPolinomico(size, a);
		cout << "El tiempo estimado es "<<tiempo<< " dias" <<endl;
	}


}