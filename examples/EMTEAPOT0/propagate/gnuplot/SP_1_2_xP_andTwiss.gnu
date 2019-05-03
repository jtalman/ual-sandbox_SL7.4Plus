set terminal x11 enhanced 2

set termopt enhanced
set lmargin 20
set rmargin 5
set format y "%+g"
set title "One turn: x' versus element for 1 micron initial delta in x"
set xlabel "element"
set ylabel "x'(element)"

set xrange [0:180]
set yrange [-4.0e-08:+4.0e-08]

#set label "+x1typ =" at -35,+0.5e-08
#set label "-x1typ =" at -35,-0.5e-08

x1typ = 1.0e-06;

stats './out/forTwiss' every :::0::0 using 5 nooutput
R21P = STATS_min/x1typ
R21PT = sprintf( "-(1+a_0^2)/b_0 x sin( mu_0 ) = R_{21} (ca %+3.1e)", R21P )
set label R21PT at +5,+3.25e-08 tc rgb "red"

stats './out/forTwiss' every :::1::1 using 5 nooutput
R21M = STATS_min/-x1typ
R21MT = sprintf( "-(1+a_0^2)/b_0 x sin( mu_0 ) = R_{21} (ca %+3.1e)", R21M )
set label R21MT at +5,-3.25e-08 tc rgb "blue"

p "out/StndrdPrtcl1" u 2:5 lt rgb "red"  w l,\
  "out/StndrdPrtcl2" u 2:5 lt rgb "blue" w l,\
  "out/forTwiss" every :::0::0 u 2:5 lc rgb "red"  pt 7 ps 3 title "(R_{21}) x (+x1typ)",\
  "out/forTwiss" every :::1::1 u 2:5 lc rgb "blue" pt 7 ps 3 title "(R_{21}) x (-x1typ)"
