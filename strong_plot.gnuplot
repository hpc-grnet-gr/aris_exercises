
## Plot strong scaling test data.

#
# Gather result data in one file
# cat mpipi-strong*.log | grep -v '^#' | sort -n -k 1 > mpipi-strong.dat
# 
# Load gnuplot module: module load gnuplot

#set terminal png
set terminal pngcairo
set output "mpipi-strong.png"
set title 'Strong Scaling Test'
set xlabel 'nprocs'
set ylabel 'time(s)'
set xtics 20
#set xrange [1:4]
set grid
#set key outside
set style data linespoints

plot "mpipi-strong.dat" using 1:3 title "pi - MPI"
