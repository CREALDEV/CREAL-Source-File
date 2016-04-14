#!/usr/bin/gnuplot
set terminal pngcairo enhanced font "arial,12" fontscale 1.0 size 1280, 720
#set title "GFR"
set output 'GFR_graph.png'
set xlabel "Time in hours"
set ylabel "Glomerular Filtration Rate (GFR) mg / deciliters"
set ytics "1"
set xtics "1"
set xrange [ 0 : 28 ] noreverse nowriteback
set yrange [ 55 : 80 ] noreverse nowriteback
set grid layerdefault   linetype 0 linewidth 1.000,  linetype 0 linewidth 1.000
plot "701_0.dat" using ($1/3600):2 notitle with lines linecolor rgb "blue" lw 5 
