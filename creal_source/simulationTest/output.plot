#!/usr/bin/gnuplot
set terminal pngcairo enhanced font "arial,12" fontscale 1.0 size 1280, 720
set output 'var.png'
set xlabel "Time in hours"
set ylabel "var"
set format y "%gk mcg"
set ytics "var"
set xtics "1"
set xrange [ 0 : 36 ] noreverse nowriteback
set yrange [ 0 : 200 ] noreverse nowriteback
set grid layerdefault   linetype 0 linewidth 1.000,  linetype 0 linewidth 1.000
plot "688_0.dat" using ($1/3600):($2/1000) notitle with lines linecolor rgb "blue" lw 5 
