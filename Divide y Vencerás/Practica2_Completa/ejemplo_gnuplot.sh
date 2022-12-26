#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "grafico.eps"
set key right bottom
set xlabel "Tamaño Vector por Insercion"
set ylabel "Tiempo en ms"
plot 'datosFinales.txt' using 1:2 t "Tiempos" w l
_end_
