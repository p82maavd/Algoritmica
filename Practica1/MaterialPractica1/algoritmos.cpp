

#include <iostream>	
#include <vector>
#include <fstream> 
#include "ClaseTiempo.cpp"
#include "sistemaEcuaciones.cpp"
#include <cmath>

using namespace std;


//1

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
	
			tiempoMedio.push_back(temporizador.elapsed());
			
		}
		double suma=0;
	
		for(int k=0;k<tiempoMedio.size();k++){
			suma+=tiempoMedio[k];
		}
		

		tiemposReales.push_back(suma/(double)repeticiones);
		numeroElementos.push_back(nMin+i*incremento);
	}
}
double sumatorio(const vector <double> &n, const vector <double> &t, int expN, int expT){

	int suma=0;
	
	for(int i=0; i< n.size();i++){

		suma+=pow(n[i],expN)*pow(t[i],expT);
	}

	return suma;
}

double sumatorioExponencial(const vector <double> &n, const vector <double> &t, int expN, int expT){

	int suma=0;
	
	for(int i=0; i< n.size();i++){

		suma+=pow(pow(2,n[i]),expN)*pow(t[i],expT);
	}

	return suma;
}

double varianza(const vector <double> &n, double media){

	int suma=0;
	

	for(int i=0; i< n.size();i++){

		suma+=pow(n[i]-media,2);
	}
	return suma/(n.size());
}

void calcularTiemposEstimadosPolinomico( const vector <double> numeroElementos, const vector <double> &a, vector<double> &tiemposEstimados){

	
	int suma;
	for(int i=0; i<numeroElementos.size();i++ ){
		suma=0;
		for(int j=0; j<a.size();j++){

			suma+=pow(numeroElementos[i],j)*a[j];
		}

		tiemposEstimados.push_back(suma);

	}

}

double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados){

	double mediaReal=0;
	double mediaEstimada=0;
	cout<<endl;
	for(int i=0; i<tiemposReales.size();i++){
		
		mediaReal+=tiemposReales[i];
		mediaEstimada+=tiemposEstimados[i];
	}
	
	mediaReal=mediaReal/tiemposReales.size();
	mediaEstimada=mediaEstimada/tiemposEstimados.size();
	double varianzaReal=varianza(tiemposReales,mediaReal);
	double varianzaEstimada=varianza(tiemposEstimados,mediaEstimada);
	cout << varianzaReal << " " << varianzaEstimada;
	return varianzaEstimada/varianzaReal;
	

}

double calcularTiempoEstimadoPolinomico(const double &n, vector <double> &a){

	double suma=0.0;
	for(int i=0; i<a.size();i++){

		suma+=(pow(n,i)*a[i])/(1000*60*60*24);
	}
	cout << endl<<suma<<endl;
	return suma;
}
void ajustePolinomico(const vector<double>&numeroElementos, const vector<double> &tiemposReales, vector<double> &a){

	int grado=a.size();
	
	vector<vector<double> > A(grado, vector<double>(grado,0));
	vector<vector<double> > B(grado, vector<double>(1,0));
	vector<vector<double> > x(grado, vector<double>(1,0));
	
	for(int i=0; i< grado; i++){
		for(int j=0; j<grado; j++){
			A[i][j]=sumatorio(numeroElementos,tiemposReales,j+i,0);
		}

	}
	
	for(int i=0;i<grado;i++){

		B[i][0]=sumatorio(numeroElementos,tiemposReales,i,1);
		
	}

	resolverSistemaEcuaciones(A,B,grado,x);
	for(int i=0;i<grado;i++){
		a[i]=x[i][0];
		
	}
	vector<double> tiemposEstimados (0);
	calcularTiemposEstimadosPolinomico(numeroElementos, a, tiemposEstimados);
	cout << endl <<"El coeficiente de determinacion es: " << calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados);

	ofstream tiempos("datosFinales.txt");
	
	for(int i=0; i<tiemposReales.size(); i++){
		tiempos << numeroElementos[i] <<  " " << tiemposReales[i]<< " " <<tiemposEstimados[i]<<endl;
	}

	tiempos.close();
	

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


void rellenarMatriz(vector < vector < double > > &A){
	double x =0.0;
	for(int i = 0; i <A[0].size(); i++){
				for(int j = 0; j < A[0].size(); j++)
				{
				  
				  x=(double)(rand()%11)/10.0;
				  
				  A[i][j]=1.05-x;
				  //cout << A[i][j] << " ";
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
	
		tiemposReales.push_back(temporizador.elapsed());
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

void calcularTiemposEstimadosExponencial(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados){
	int suma;
	for(int i=0; i<numeroElementos.size();i++ ){
		suma=0;
		for(int j=0; j<a.size();j++){

			suma+=pow(pow(2,numeroElementos[i]),j)*a[j];
		}

		tiemposEstimados.push_back(suma);

	}
}

double calcularTiempoEstimadoExponencial(const double &numeroElementos, const vector <double> &a){
	return 0.0;
}


void ajusteExponencial(const vector <double> &numeroElementos, const vector<double> &tiemposReales, vector <double> &a){
	int grado=a.size();
	
	vector<vector<double> > A(grado, vector<double>(grado,0));
	vector<vector<double> > B(grado, vector<double>(1,0));
	vector<vector<double> > x(grado, vector<double>(1,0));
	
	for(int i=0; i< grado; i++){
		for(int j=0; j<grado; j++){
			A[i][j]=sumatorioExponencial(numeroElementos,tiemposReales,j+i,0);
		}

	}
	
	for(int i=0;i<grado;i++){

		B[i][0]=sumatorioExponencial(numeroElementos,tiemposReales,i,1);
		
	}

	resolverSistemaEcuaciones(A,B,grado,x);
	for(int i=0;i<grado;i++){
		a[i]=x[i][0];
		
	}
	vector<double> tiemposEstimados (0);
	calcularTiemposEstimadosExponencial(numeroElementos, a, tiemposEstimados);
	cout << endl <<"El coeficiente de determinacion es: " << calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados);

	ofstream tiempos("datosFinales.txt");
	
	for(int i=0; i<tiemposReales.size(); i++){
		tiempos << numeroElementos[i] <<  " " << tiemposReales[i]<< " " <<tiemposEstimados[i]<<endl;
	}

	tiempos.close();

}


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
	
		tiemposReales.push_back(temporizador.elapsed());
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
	cout << "Tamaño de a: "<<a.size();
	cout<<endl<<"La funcion de la curva es: " << a[0] << " + " << a[1]<<"2^n "<<endl;
	double tiempo=0.0;
	double size=1.0;
	while(size!=0){
		cout << endl<<"Para que tamaño quieres calcular el tiempo Estimado? ";
		
		cin>>size;
		tiempo=calcularTiempoEstimadoPolinomico(size, a);
		cout << "El tiempo estimado es "<<tiempo<< " dias" <<endl;
	}



}