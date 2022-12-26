
#include "funciones.hpp"
#include <iostream>

using namespace std;

int main()
{
	
	while(true){
		
		cout<< endl <<"Programa principal: " << endl;
		cout << endl << "1. Problema de las N-Reinas";
		cout << endl << "2. Problema de las N-Reinas con 1ª reina en casilla central";
		cout << endl << "3. Problema de las N-Reinas Las Vegas";

		int option=0;

		cout << endl <<endl <<"Opción elegida: ";
		cin>>option;

		if(option == 1){

			nreinas();
		}

		else if(option==2){

			nreinascentral();
		}

		else if(option==3){
			
			nreinaslasvegas();
		}

		else{
			cout<<"Opción no válida"<<endl;
			return 0;
		}
	}

}