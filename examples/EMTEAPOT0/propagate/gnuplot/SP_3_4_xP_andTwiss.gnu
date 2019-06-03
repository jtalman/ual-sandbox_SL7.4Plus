set terminal x11 enhanced 4
set termopt enhanced
set lmargin 20
set rmargin 5
set format y "%+g"
set title "One turn: x' versus element for 1 micron initial delta in x'"
set xlabel "element"
set ylabel "x'(element)"

set xrange [0:250]
set yrange [-1.5e-06:+1.5e-06]

#set label "+x2typ =" at -35,+1.0e-06
#set label "-x2typ =" at -35,-1.0e-06

x2typ = 1.0e-06;

stats './out/forTwiss' every :::2::2 using 5 nooutput
R22P = STATS_min/x2typ
R22PT = sprintf( "cos( mu_0 ) - a_0 sin( mu_0 ) = R_{22} (ca %+3.1e)", R22P )
set label R22PT at +5,+1.25e-06 tc rgb "red"

stats './out/forTwiss' every :::3::3 using 5 nooutput
R22M = STATS_min/-x2typ
R22MT = sprintf( "cos( mu_0 ) - a_0 sin( mu_0 ) = R_{22} (ca %+3.1e)", R22M )
set label R22MT at +5,-1.25e-06 tc rgb "blue"

p "out/StndrdPrtcl3" u 2:5 lt rgb "red"  w l,\
  "out/StndrdPrtcl4" u 2:5 lt rgb "blue" w l,\
  "out/forTwiss" every :::2::2 u 2:5 lc rgb "red"  pt 7 ps 3 title "(R_{22}) x (+x2typ)",\
  "out/forTwiss" every :::3::3 u 2:5 lc rgb "blue" pt 7 ps 3 title "(R_{22}) x (-x2typ)"
