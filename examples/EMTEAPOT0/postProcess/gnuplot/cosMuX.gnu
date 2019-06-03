set title "cosMuX"
set xlabel "Element"
set ylabel "cosMuX(s)"
set yrange [-0.961:-0.963]

p "./out/cosMuX" u 1:2 w l
