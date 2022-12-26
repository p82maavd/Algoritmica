
#include "funciones.hpp"

using namespace std;

double sumatorio(const vector <double> &n, const vector <double> &t, int expN, int expT){

	double suma=0.0;
	
	for(int i=0; i< n.size();i++){

		suma+=pow(n[i],expN)*pow(t[i],expT);
	}

	return suma;
}

double sumatorioExponencial(const vector <double> &n, const vector <double> &t, int expN, int expT){

	double suma=0.0;
	
	for(int i=0; i< n.size();i++){

		suma+=pow(pow(2,n[i]),expN)*pow(t[i],expT);
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

void calcularTiemposEstimadosPolinomico( const vector <double> numeroElementos, const vector <double> &a, vector<double> &tiemposEstimados){

	double suma;
	for(int i=0; i<numeroElementos.size();i++ ){
		suma=0.0;
		for(int j=0; j<a.size();j++){
			suma+=pow(numeroElementos[i],j)*a[j];
		}

		tiemposEstimados.push_back(suma);
	}

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

double calcularTiempoEstimadoPolinomico(const double &n, vector <double> &a){

	double suma=0.0;
	for(int i=0; i<a.size();i++){

		suma+=(pow(n,i)*a[i])/(1000*60*60*24);
	}
	
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

void calcularTiemposEstimadosExponencial(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados){
	cout << endl << a[0] << " " <<a[1] <<endl;
	for(int i=0; i<numeroElementos.size();i++ ){
		
		tiemposEstimados.push_back(a[0]+a[1]*pow(2,numeroElementos[i]));

	}
}

double calcularTiempoEstimadoExponencial(const double &numeroElementos, const vector <double> &a){
	return (a[0]+a[1]*pow(2,numeroElementos))/(1000*60*60*24);
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

