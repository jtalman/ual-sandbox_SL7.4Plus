# The purpose for this gnuplot file is to produce one plot for each
# line in the userBunch file and, for lines 10 through 18 to attach 
# the p[0] p[1] p[2] p[3] p[4] p[5] entries as graph title.
# Of course you have to check that the entries in this file match
# the entries in the userBunch file.

# set terminal postscript eps enhanced color 20
# set output "SpinEvolve.eps"
set grid
set xlabel 'turn index'
set ylabel 'S[0]'

set terminal x11 0
set title " 0.01, 0, 0, 0, 0, 5.85e-5"
p 'IG' i 0 u 2:10 w l lw 1

set terminal x11 1
set title " +x1typ, 0, 0, 0, 0, 0"
p 'IG' i 1 u 2:10 w l lw 1

set terminal x11 2
set title "-x1typ, 0, 0, 0, 0, 0"
p 'IG' i 2 u 2:10 w l lw 1

set terminal x11 3
set title " 0, +x2typ, 0, 0, 0, 0"
p 'IG' i 3 u 2:10 w l lw 1

set terminal x11 4
set title " 0, -x2typ, 0, 0, 0, 0"
p 'IG' i 4 u 2:10 w l lw 1

set terminal x11 5
set title " 0, 0, +y1typ, 0, 0, 0"
p 'IG' i 5 u 2:10 w l lw 1

set terminal x11 6
set title " 0, 0, -y1typ, 0, 0, 0"
p 'IG' i 6 u 2:10 w l lw 1

set terminal x11 7
set title " 0, 0, 0, +y2typ, 0, 0"
p 'IG' i 7 u 2:10 w l lw 1

set terminal x11 8
set title " 0, 0, 0, -y2typ, 0, 0"
p 'IG' i 8 u 2:10 w l lw 1

set terminal x11 9
set title " 0, 0, 0, 0, 0, +deltyp"
p 'IG' i 9 u 2:10 w l lw 1

set terminal x11 10
set title " 0, 0, 0, 0, 0, -deltyp"
p 'IG' i 10 u 2:10 w l lw 1

set terminal x11 11
set title "0.005, 0, 0, 0, 0, 0"
p 'IG' i 11 u 2:10 w l lw 1

set terminal x11 12
set title "-0.005, 0, 0, 0, 0, 0"
p 'IG' i 12 u 2:10 w l lw 1

set terminal x11 13
set title " 0, 0.0002, 0, 0, 0, 0"
p 'IG' i 13 u 2:10 w l lw 1

set terminal x11 14
set title " 0, -0.0002, 0, 0, 0, 0"
p 'IG' i 14 u 2:10 w l lw 1

set terminal x11 15
set title "0, 0, 0.01, 0, 0, 0"
p 'IG' i 15 u 2:10 w l lw 1

set terminal x11 16
set title " 0, 0, 0, 0.001, 0, 0"
p 'IG' i 16 u 2:10 w l lw 1

set terminal x11 17
set title "0, 0, 0, 0, 0, 5.85e-5"
p 'IG' i 17 u 2:10 w l lw 1

set terminal x11 18
set title "0, 0, 0, 0, 0,-5.85e-5"
p 'IG' i 18 u 2:10 w l lw 1

set terminal x11 19
set title " 0, 0, 0, 0, 0, 0"
p 'IG' i 19 u 2:10 w l lw 1
