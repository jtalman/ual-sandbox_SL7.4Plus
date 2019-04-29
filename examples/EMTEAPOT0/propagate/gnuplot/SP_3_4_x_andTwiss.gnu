set terminal x11 enhanced 3
set termopt enhanced
set lmargin 20
set rmargin 5
set format y "%+g"
set title "One turn: x versus element for 1 micron initial delta in x'"
set xlabel "element"
set ylabel "x(element)"

set xrange [0:180]
set yrange [-5.0e-05:+5.0e-05]

#set label "+x2typ =" at -35,+4.6e-05
#set label "-x2typ =" at -35,-4.6e-05

x2typ = 1.0e-06;

stats './out/forTwiss' every :::2::2 using 4 nooutput
R12P = STATS_min/x2typ
R12PT = sprintf( "R_{12} = %+e = b_0 x sin( mu_0 )", R12P )
set label R12PT at +5,-4.6e-05 tc rgb "red"

stats './out/forTwiss' every :::3::3 using 4 nooutput
R12M = STATS_min/-x2typ
R12MT = sprintf( "R_{12} = %+e = b_0 x sin( mu_0 )", R12M )
set label R12MT at +5,+4.6e-05 tc rgb "blue"

p "out/StndrdPrtcl3" u 2:4 lt rgb "red"  w l,\
  "out/StndrdPrtcl4" u 2:4 lt rgb "blue" w l,\
  "out/forTwiss" every :::2::2 u 2:4 lc rgb "red"  pt 7 ps 3 title "(R_{12}) x (+x2typ)",\
  "out/forTwiss" every :::3::3 u 2:4 lc rgb "blue" pt 7 ps 3 title "(R_{12}) x (-x2typ)"
