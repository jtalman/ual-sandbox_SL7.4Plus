set title "cosMu_iX"
set xlabel "Element"
set ylabel "cosMu_iX(s)"
set yrange [-0.961:-0.963]

p "./out/cosMu_iX" u 1:2 w l
