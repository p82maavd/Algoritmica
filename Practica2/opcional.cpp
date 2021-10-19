




void opcional(){

	vector<double> tiemposReales(0), numeroElementos(0), a(2);
	tiemposOrdenacionQuickSort(1000000,1000000,1,1,tiemposReales,numeroElementos);
	ajusteLogaritmico(numeroElementos, tiemposReales, a);

	cout<<endl<<"La funcion de la curva es: " << a[0] << " + " << a[1]<<"nlogn+ "<<endl;

	double size=1.0;
	while(size!=0){
		cout << endl<<"Para que tamaño quieres calcular el tiempo Estimado? ";
		
		cin>>size;
		cout << "El tiempo estimado es "<<calcularTiempoEstimadoLogaritmico(size, a)<< " dias" <<endl;
	}
	

}