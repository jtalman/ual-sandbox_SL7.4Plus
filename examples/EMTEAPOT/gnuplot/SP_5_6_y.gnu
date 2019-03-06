set title "One turn: y versus element for 1 micron initial delta in y"
set xlabel "element"
set ylabel "y as a Function of element"
p "out/StndrdPrtcl5" u 2:6 w l, "out/StndrdPrtcl6" u 2:6 w l
