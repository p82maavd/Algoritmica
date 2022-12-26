
#include "funciones.hpp"

using namespace std;

void rellenarVector(vector<int> &v){
	
	for(int i =0 ; i< v.size();i++){
		v[i]= rand()%1000000;
	}

}

bool estaOrdenado(vector<int> v){
	
	for(int i=0; i<v.size()-1;i++){
		if(v[i]>v[i+1]){
			
			return false;
		}
	}
	return true;
}

void insercion(vector<int> &v, int low, int high){
	int i, key, j;

    for (i = low; i <= high; i++)
    {
        key = v[i];

        j = i-1;

        /* Move elements of arr[0..i-1], that are
         greater than key, to one position ahead
         of their current position */
        while (j >= 0 && v[j] > key)
        {
            v[j+1] = v[j];
            j = j-1;
        }
        v[j+1] = key;
    }
}

double sumatorio(const vector <double> &n, const vector <double> &t, int expN, int expT){

	double suma=0.0;
	
	for(int i=0; i< n.size();i++){

		suma+=pow(n[i],expN)*pow(t[i],expT);
	}

	return suma;
}

double sumatorioLogaritmico(const vector <double> &n, const vector <double> &t, int expN, int expT){

	double suma=0.0;
	
	for(int i=0; i< n.size();i++){

		suma+=pow(n[i]*log(n[i]),expN)*pow(t[i],expT);
	}

	return suma;
}

double varianza(const vector <double> &n, double media){

	double suma=0.0;
	

	for(int i=0; i< n.size();i++){

		suma+=pow(n[i]-media,2);
	}
	return suma/(n.size()-1);
}


double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados){

	double mediaReal=0.0;
	double mediaEstimada=0.0;
	
	for(int i=0; i<tiemposReales.size();i++){
		
		mediaReal+=tiemposReales[i];
		mediaEstimada+=tiemposEstimados[i];
	}
	
	mediaReal=mediaReal/tiemposReales.size();
	mediaEstimada=mediaEstimada/tiemposEstimados.size();
	double varianzaReal=varianza(tiemposReales,mediaReal);
	double varianzaEstimada=varianza(tiemposEstimados,mediaEstimada);
	//cout << varianzaReal << " " << varianzaEstimada;
	return varianzaEstimada/varianzaReal;
	

}

void calcularTiemposEstimadosLogaritmico(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados){
	cout << endl << a[0] << " " <<a[1] <<endl;
	for(int i=0; i<numeroElementos.size();i++ ){
		
		tiemposEstimados.push_back(a[0]+a[1]*numeroElementos[i]*log(numeroElementos[i]));

	}
}

double calcularTiempoEstimadoLogaritmico(const double &numeroElementos, const vector <double> &a){
	return (a[0]+a[1]*numeroElementos*log(numeroElementos))/(1000*60*60*24);
}


void ajusteLogaritmico(const vector <double> &numeroElementos, const vector<double> &tiemposReales, vector <double> &a){
	
	int grado=a.size();
	
	vector<vector<double> > A(grado, vector<double>(grado,0));
	vector<vector<double> > B(grado, vector<double>(1,0));
	vector<vector<double> > x(grado, vector<double>(1,0));
	
	for(int i=0; i< grado; i++){
		for(int j=0; j<grado; j++){
			A[i][j]=sumatorioLogaritmico(numeroElementos,tiemposReales,j+i,0);
		}
	}
	
	for(int i=0;i<grado;i++){
		B[i][0]=sumatorioLogaritmico(numeroElementos,tiemposReales,i,1);
	}

	resolverSistemaEcuaciones(A,B,grado,x);
	for(int i=0;i<grado;i++){
		a[i]=x[i][0];
		
	}
	vector<double> tiemposEstimados (0);
	calcularTiemposEstimadosLogaritmico(numeroElementos, a, tiemposEstimados);
	cout << endl <<"El coeficiente de determinacion es: " << calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados);

	ofstream tiempos("datosFinales.txt");
	
	for(int i=0; i<tiemposReales.size(); i++){
		tiempos << numeroElementos[i] <<  " " << tiemposReales[i]<< " " <<tiemposEstimados[i]<<endl;
	}

	tiempos.close();

}

void tiemposOrdenacionComparacion(int nMin, int nMax, int repeticiones, int incremento, vector<double> &tiemposQuickSort,vector<double> &tiemposFusion,vector<double> &numeroElementos){

	int iteraciones= (nMax-nMin)/incremento;

	for(int i=0; i< iteraciones+1; i++){

		vector<int> v(nMin+i*incremento);
		
		Clock temporizadorQuickSort, temporizadorFusion;
		vector<double> tiempoMedioQuickSort(0);
		vector<double> tiempoMedioFusion(0);


		for(int j=0; j< repeticiones; j++){

			rellenarVector(v);
			vector<int> v2=v;
			
			temporizadorQuickSort.start();

			quicksort(v,0,v.size()-1,0);
			
			temporizadorQuickSort.stop();

			temporizadorFusion.start();

			fusion(v2,0);
			
			temporizadorFusion.stop();

			if(estaOrdenado(v)==false || estaOrdenado(v2)==false){
				cout << "NO ESTA ORDENADO"<<endl;
			}
			
			tiempoMedioQuickSort.push_back(temporizadorQuickSort.elapsed()/1000);
			tiempoMedioFusion.push_back(temporizadorFusion.elapsed()/1000);
			
		}
		double sumaQuickSort=0;
		double sumaFusion=0;
	
		for(int k=0;k<tiempoMedioQuickSort.size();k++){
			sumaQuickSort+=tiempoMedioQuickSort[k];
			sumaFusion+=tiempoMedioFusion[k];
		}
		

		tiemposQuickSort.push_back(sumaQuickSort/(double)repeticiones);
		tiemposFusion.push_back(sumaFusion/(double)repeticiones);
		numeroElementos.push_back(nMin+i*incremento);
		
	}

}

void comparacion(){


	int min, max, incremento, iter, rango;

	cout<<"Introduce el valor minimo de elementos del vector: ";
	cin>>min;

	cout<<"Introduce el valor maximo de elementos del vector: ";
	cin>>max;

	cout<<"Introduce el incremento de elementos del vector: ";
	cin>>incremento;

	cout<<"Introduce el numero de iteraciones por cada numero de elementos: ";
	cin>>iter;

	vector<double> tiemposQuickSort(0), tiemposFusion(0), numeroElementos(0);
	tiemposOrdenacionComparacion(min,max,iter,incremento,tiemposQuickSort,tiemposFusion,numeroElementos);


	ofstream tiempos("datosComparacion.txt");
	
	for(int i=0; i<tiemposQuickSort.size(); i++){
		tiempos << numeroElementos[i] <<  " " << tiemposQuickSort[i]<< " " <<tiemposFusion[i]<<endl;
	}

	tiempos.close();

	system("./comparacion.sh");
	//system("eog grafico.png");
}

