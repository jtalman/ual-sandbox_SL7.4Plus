set terminal x11 enhanced 7

set termopt enhanced
set lmargin 20
set rmargin 5
set format y "%+g"
set title "One turn: y versus element for THE ZERO (0) input"
set xlabel "element"
set ylabel "x(element)"

set xrange [0:180]
set yrange [-1.5e-06:+1.5e-06]

x1typ = 1.0e-06;

p "out/StndrdPrtcl0" u 2:6 lt rgb "red"  w l
