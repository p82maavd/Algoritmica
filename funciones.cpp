
#include "funciones.hpp"

using namespace std;

void rellenarVector(vector<int> v){

	for(int i =0 ; i< v.size();i++){

		v[i]= rand()%10000000;

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

void insercion(vector<int> &v){
	for (int i=1; i<v.size(); i++){
    	int temp = v[i];
        int j = i - 1;
        while ( (v[j] > temp) && (j >= 0) ){
        	v[j+1] = v[j];
        	j--;
		}	
        v[j+1] = temp;
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

