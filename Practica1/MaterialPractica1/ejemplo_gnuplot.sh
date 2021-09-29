#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "grafico.eps"
set key right bottom
set xlabel "Tamaño"
set ylabel "Tiempo"
plot 'datosFinales.txt' using 1:2 t "Tiempos Reales" w l, 'datosFinales.txt' using 1:3 t "Tiempos Estimados" w l
_end_
