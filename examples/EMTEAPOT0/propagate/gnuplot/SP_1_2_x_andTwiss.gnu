set terminal x11 enhanced 1

set termopt enhanced
set lmargin 20
set rmargin 5
set format y "%+g"
set title "One turn: x versus element for 1 micron initial delta in x"
set xlabel "element"
set ylabel "x(element)"

set xrange [0:180]
set yrange [-1.5e-06:+1.5e-06]

#set label "+x1typ =" at -35,+1.0e-06
#set label "-x1typ =" at -35,-1.0e-06

x1typ = 1.0e-06;

stats './out/forTwiss' every :::0::0 using 4 nooutput
R11P = STATS_min/x1typ
R11PT = sprintf( "R_{11} = %+e = cos( mu_0 ) + a_0 sin( mu_0 )", R11P )
set label R11PT at +5,+1.25e-06 tc rgb "red"

stats './out/forTwiss' every :::1::1 using 4 nooutput
R11M = STATS_min/-x1typ
R11MT = sprintf( "R_{11} = %+e = cos( mu_0 ) + a_0 sin( mu_0 )", R11M )
set label R11MT at +5,-1.25e-06 tc rgb "blue"

p "out/StndrdPrtcl1" u 2:4 lt rgb "red"  w l,\
  "out/StndrdPrtcl2" u 2:4 lt rgb "blue" w l,\
  "out/forTwiss" every :::0::0 u 2:4 lc rgb "red"  pt 7 ps 3 title "(R_{11}) x (+x1typ)",\
  "out/forTwiss" every :::1::1 u 2:4 lc rgb "blue" pt 7 ps 3 title "(R_{11}) x (-x1typ)"
