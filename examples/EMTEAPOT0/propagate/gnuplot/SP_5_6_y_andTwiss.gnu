#set encoding utf8 
set terminal x11 enhanced 3

set termopt enhanced
set lmargin 20
set rmargin 5
set format y "%+g"
set title "One turn: y versus element for 1 micron initial delta in y"
set key font ",10"
set xlabel "element"
set ylabel "y(element)"

set xrange [0:180]
set yrange [-2.0e-06:+2.0e-06]

set label "+x3typ =" at -35,+1.0e-06
set label "-x3typ =" at -35,-1.0e-06

x3typ = 1.0e-06;

stats './out/forTwiss' every :::4::4 using 6 nooutput
#print STATS_blocks 
#print STATS_min 
R12P = STATS_min/x3typ
R12PT = sprintf( "R_{12} = %g = b_0 sin( mu_0 )", R12P )
set label R12PT at +5,+1.25e-06 tc rgb "red"

stats './out/forTwiss' every :::5::5 using 6 nooutput
R12M = STATS_min/-x3typ
R12MT = sprintf( "R_{12} = %g = b_0 sin( mu_0 )", R12M )
set label R12MT at +5,-1.25e-06 tc rgb "blue"

p "out/StndrdPrtcl5" u 2:6 lt rgb "red"  w l,\
  "out/StndrdPrtcl6" u 2:6 lt rgb "blue" w l,\
  "out/forTwiss" every :::4::4 u 2:6 lc rgb "red"  pt 7 ps 3 title "(R_{21}) x (+x3typ)",\
  "out/forTwiss" every :::5::5 u 2:6 lc rgb "blue" pt 7 ps 3 title "(R_{21}) x (-x3typ)"

