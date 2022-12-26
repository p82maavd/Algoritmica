
#include "funciones.hpp"


int main()
{
	srand(time(NULL));
	using namespace std;

	while(true){
		cout<< endl <<"Programa principal: " << endl;

		cout << endl << "1. Ordenación Seleccion";
		cout << endl << "2. Producto Matrices Cuadradas";
		cout << endl << "3. Fibonacci Recursivo";
		cout << endl << "4. Salir";


		int option=0;

		cout << endl <<" Opción elegida: ";
		cin>>option;

		if(option == 1){

			ordenacionSeleccion();
		}

		else if(option==2){

			productoMatricesCuadradas();
		}

		else if(option==3){

			fibonacciRecursivo();
		}

		else if(option==4){
			
			return 0;
		}

		else{
			cout<<"Opción no válida"<<endl;
			return 0;
		}
	}

}