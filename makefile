main: main.o ordenacionFusion.o ordenacionQuickSort.o  sistemaEcuaciones.o clean
	g++ main.cpp ordenacionQuickSort.cpp ordenacionFusion.cpp funciones.cpp sistemaEcuaciones.cpp

clean:
	rm *.o
