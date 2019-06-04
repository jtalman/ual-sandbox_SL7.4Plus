set title "beta_iX"
set xlabel "Element"
set ylabel "beta_iX(s)"
set yrange [+30.0:+40.0]

p "./out/beta_iX" u 1:2 w l
