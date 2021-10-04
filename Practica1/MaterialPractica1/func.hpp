

void rellenarVector(vector<int> v);
bool seleccion(vector<int> v);
bool estaOrdenado(vector<int> v);
void tiemposOrdenacionSeleccion(int nMin, int nMax, int repeticiones, int incremento, vector <double> &tiemposReales, vector <double> &numeroElementos);
double sumatorio(const vector <double> &n, const vector <double> &t, int expN, int expT);
double sumatorioExponencial(const vector <double> &n, const vector <double> &t, int expN, int expT);
double varianza(const vector <double> &n, double media);
void calcularTiemposEstimadosPolinomico( const vector <double> numeroElementos, const vector <double> &a, vector<double> &tiemposEstimados);
double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados);
double calcularTiempoEstimadoPolinomico(const double &n, vector <double> &a);
void ajustePolinomico(const vector<double>&numeroElementos, const vector<double> &tiemposReales, vector<double> &a);
void ordenacionSeleccion();


void rellenarMatriz(vector < vector < double > > &A);
void multiplicarMatrices2(const vector < vector < double > > &m1, const vector < vector < double > > &m2, vector < vector < double > > &producto);
void tiemposMatricesCuadradas(int nMin, int nMax, int incremento, vector <double> &tiemposReales, vector <double> &numeroElementos);
void productoMatricesCuadradas();


void calcularTiemposEstimadosExponencial(const vector <double> &numeroElementos, const vector <double> &a, vector <double> &tiemposEstimados);
double calcularTiempoEstimadoExponencial(const double &numeroElementos, const vector <double> &a);
void ajusteExponencial(const vector <double> &numeroElementos, const vector<double> &tiemposReales, vector <double> &a);


int fibonacci(int num);
void tiemposFibonacciRecursivo(int nMin, int nMax, int incremento, vector <double> &tiemposReales, vector <double> &numeroElementos);
void fibonacciRecursivo();

