
#include "funciones.hpp"
#include <iostream>

using namespace std;

int main()
{
	
	while(true){
		
		cout<< endl <<"Programa principal: " << endl;
		cout << endl << "1. Problema del Cambio";
		cout << endl << "2. Problema de la mochila";
		cout << endl << "3. Salir";

		int option=0;

		cout << endl <<"Opción elegida: ";
		cin>>option;

		if(option == 1){

			cambio();
		}

		else if(option==2){

			mochila();
		}

		else if(option==3){
			
			return 0;
		}


		else{
			cout<<"Opción no válida"<<endl;
			return 0;
		}
	}

}