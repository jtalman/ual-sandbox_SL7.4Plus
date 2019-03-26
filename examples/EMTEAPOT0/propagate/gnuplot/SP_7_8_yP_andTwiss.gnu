set encoding utf8 
set terminal x11 enhanced 4

set termopt enhanced
set lmargin 20
set rmargin 5
set format y "%+g"
set title "One turn: y' versus element for 1 micron initial delta in y'"
set key font ",10"
set xlabel "element"
set ylabel "y'(element)"

set xrange [0:180]
set yrange [-2.0e-06:+2.0e-06]

set label "+x4typ =" at -35,+1.0e-06
set label "-x4typ =" at -35,-1.0e-06

x4typ = 1.0e-06;

stats './out/forTwiss' every :::6::6 using 7 nooutput
#print STATS_blocks 
#print STATS_min 
R22P = STATS_min/x4typ
R22PT = sprintf( "R_{22} = %g = cos( mu_0 ) - a_0sin( mu_0 )", R22P )
set label R22PT at +5,+1.25e-06 tc rgb "red"

stats './out/forTwiss' every :::7::7 using 7 nooutput
R22M = STATS_min/-x4typ
R22MT = sprintf( "R_{22} = %g = cos( mu_0 ) - a_0sin( mu_0 )", R22M )
set label R22MT at +5,-1.25e-06 tc rgb "blue"

p "out/StndrdPrtcl7" u 2:7 lt rgb "red"  w l,\
  "out/StndrdPrtcl8" u 2:7 lt rgb "blue" w l,\
  "out/forTwiss" every :::6::6 u 2:7 lc rgb "red"  pt 7 ps 3 title "(R_{22}) x (+x4typ)",\
  "out/forTwiss" every :::7::7 u 2:7 lc rgb "blue" pt 7 ps 3 title "(R_{22}) x (-x4typ)"

