set title "cosMuX"
set xlabel "Element"
set ylabel "cosMuX(s)"
set yrange [-0.962300:-0.962302]

p "./out/cosMuX" u 1:2 w l
