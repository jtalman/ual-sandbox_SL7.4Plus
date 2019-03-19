set terminal x11 4
set title "One turn: y' versus element for 1 micron initial delta in y'"
set xlabel "element"
set ylabel "y'' as a Function of element"
p "out/StndrdPrtcl7" u 2:7 w l, "out/StndrdPrtcl8" u 2:7 w l
