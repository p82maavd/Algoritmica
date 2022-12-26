#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream> 
#include <cmath>
#include "ClaseTiempo.cpp"
#include "sistemaEcuaciones.hpp"



using namespace std;

void rellenarVector(vector<int> &v);
bool estaOrdenado(vector<int> v);
void insercion(vector<int> &v, int low, int high);
double sumatorioLogaritmico(const vector <double> &n, const vector <double> &t, int expN, int expT);
double varianza(const vector <double> &n, double media);
double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados);

void ajusteLogaritmico(const vector <double> &numeroElementos, const vector<double> &tiemposReales, vector <double> &a);

void calcularTiemposEstimadosLogaritmico(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados);
double calcularTiempoEstimadoLogaritmico(const double &numeroElementos, const vector <double> &a);

void quicksort(vector<int> &v, int low, int high, int size);
void extraquicksort(vector<int> &v, int low, int high, int n);
void tiemposOrdenacionQuickSort(int nMin, int nMax, int repeticiones, int incremento, vector <double> &tiemposReales, vector <double> &numeroElementos);
void tiemposOrdenacionExtraQuickSort( vector <double> &tiemposReales, vector <double> &numeroElementos);
void ordenacionQuickSort();
void ordenacionExtraQuickSort();


void fusion(vector<int> &t, int n);
void tiemposOrdenacionFusion(int nMin, int nMax, int repeticiones, int incremento, vector <double> &tiemposReales, vector <double> &numeroElementos);
void ordenacionFusion();
void ordenacionExtraFusion();

void comparacion();
