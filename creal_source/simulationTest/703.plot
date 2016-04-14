#!/usr/bin/gnuplot
set terminal pngcairo enhanced font "arial,12" fontscale 1.0 size 1280, 720 
#set title "Blood Glucose Level Type II Diabetes Patient"
set output 'bloodG_graph.png'
set xlabel "Time in hours"
set ylabel "Blood Glucose Level Type II Diabetes Patient mL / min./1.73m^2"
set ytics "10"
set xtics "1"
set xrange [ 0 : 28 ] noreverse nowriteback
set grid layerdefault   linetype 0 linewidth 1.000,  linetype 0 linewidth 1.000
plot "703_0.dat" using ($1/3600):2 notitle with lines linecolor rgb "blue" lw 5 

