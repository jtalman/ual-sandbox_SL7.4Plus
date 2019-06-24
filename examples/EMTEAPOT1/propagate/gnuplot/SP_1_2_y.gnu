set title "One turn: y versus element for 1 micron initial delta in x"
set xlabel "element"
set ylabel "y as a Function of element"
p "out/StndrdPrtcl1" u 2:6 w l, "out/StndrdPrtcl2" u 2:6 w l
