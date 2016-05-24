
## Plot weak scaling test data.

#
# Gather result data in one file
# cat mpipi-weak*.log | grep -v '^#' | sort -n -k 1 > mpipi-weak.dat
# 
# Load gnuplot module: module load gnuplot

#set terminal png
set terminal pngcairo
set output "mpipi-weak.png"
set title 'Weak Scaling Test'
set xlabel 'nprocs'
set ylabel 'time(s)'
#set yrange [0:0.5]
set xtics 20
#set ytics 0.1
set yrange [0:120]
set grid
#set key outside
set style data linespoints

plot "mpipi-weak.dat" using 1:3 title "pi - MPI"
