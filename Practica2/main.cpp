
#include "funciones.hpp"


int main()
{
	srand(time(NULL));
	using namespace std;

	while(true){
		cout<< endl <<"Programa principal: " << endl;

		cout << endl << "1. Ordenación Quicksort";
		cout << endl << "2. Ordenación Fusión";
		cout << endl << "3. Ordenación Extra Quicksort";
		cout << endl << "4. Ordenación Extra Fusion";
		cout << endl << "5. Salir";


		int option=0;

		cout << endl <<" Opción elegida: ";
		cin>>option;

		if(option == 1){

			ordenacionQuickSort();
		}

		else if(option==2){

			ordenacionFusion();
		}

		else if(option==3){
			
			ordenacionExtraQuickSort();
		}

		else if(option==4){
			
			ordenacionExtraFusion();
		}

		else if(option==5){
			
			return 0;
		}

		else{
			cout<<"Opción no válida"<<endl;
			return 0;
		}
	}

}