set terminal postscript
set output "times_1024.ps"

set logscale xy 2
set grid xtics ytics
show logscale

set title "TLB Size Measurement"
set ylabel "Time Per Access (ns)"
set xlabel "Number of Pages"
plot "times_1024.txt" with lines
pause -1 "Hit any key to continue"
