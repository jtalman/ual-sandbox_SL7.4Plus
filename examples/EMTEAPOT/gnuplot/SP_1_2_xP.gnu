set title "One turn: x' versus element for 1 micron initial delta in x"
set xlabel "element"
set ylabel "x' as a Function of element"
p "out/StndrdPrtcl1" u 2:5 w l, "out/StndrdPrtcl2" u 2:5 w l
