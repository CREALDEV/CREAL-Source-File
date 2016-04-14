#!/usr/bin/gnuplot
 
set title "GFR "
set output 'GFR_graph.png'
set xlabel "Time"
set ylabel "Y"
set ytics "10"
#set style line 1 lt 1 lw 3 pt 3 linecolor rgb "blue"
plot "701_0.dat" title "HELLO" with lines linecolor rgb "blue" 
#pause -1 "Hit any key to continue"
