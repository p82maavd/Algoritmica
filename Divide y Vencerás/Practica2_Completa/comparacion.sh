#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "grafico.eps"
set key right bottom
set xlabel "Tamaño"
set ylabel "Tiempo en ms"
plot 'datosComparacion.txt' using 1:2 t "Tiempos Quicksort" w l, 'datosComparacion.txt' using 1:3 t "Tiempos Fusion" w l
_end_
