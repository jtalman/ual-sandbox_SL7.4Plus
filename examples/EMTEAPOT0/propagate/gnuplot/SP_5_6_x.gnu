set title "One turn: x versus element for 1 micron initial delta in y"
set xlabel "element"
set ylabel "x as a Function of element"
p "out/StndrdPrtcl5" u 2:4 w l, "out/StndrdPrtcl4" u 2:6 w l
