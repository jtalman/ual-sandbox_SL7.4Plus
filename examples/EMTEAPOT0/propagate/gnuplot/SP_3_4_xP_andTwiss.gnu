#set print "-"
#set encoding utf8 
#set terminal x11 enhanced font "terminal-16" 1
#set terminal x11 enhanced font "arial,15" 1
 set terminal x11 enhanced 2
#set terminal postscript
#set term post
#set out '|gs -q -'

set termopt enhanced
#set border 100
#set size 1,1
 set lmargin 20
 set rmargin 5
#set format y "+%e4.1"
#set format y "%.2t*10^%+03T"
#set format y "+%4.1t e+2.0"
 set format y "%+g"
set title "One turn: x' versus element for 1 micron initial delta in x'"
set key font ",10"
set xlabel "element"
set ylabel "x'(element)"

set xrange [0:180]
set yrange [-2.0e-06:+2.0e-06]

set label "+x2typ =" at -35,+1.0e-06
set label "-x2typ =" at -35,-1.0e-06

x2typ = 1.0e-06;

stats './out/forTwiss' every :::2::2 using 5 nooutput
#print STATS_blocks 
#print STATS_min 
R21P = STATS_min/x2typ
R21PT = sprintf( "R_{21} = %g = -(1+a_0^2) x sin( mu_0 ) / b_0", R21P )
set label R21PT at +5,+1.25e-06 tc rgb "red"

stats './out/forTwiss' every :::3::3 using 5 nooutput
R21M = STATS_min/-x2typ
R21MT = sprintf( "R_{21} = %g = -(1+a_0^2) x sin( mu_0 ) / b_0", R21M )
set label R21MT at +5,-1.25e-06 tc rgb "blue"

p "out/StndrdPrtcl3" u 2:5 lt rgb "red"  w l,\
  "out/StndrdPrtcl4" u 2:5 lt rgb "blue" w l,\
  "out/forTwiss" every :::2::2 u 2:5 lc rgb "red"  pt 7 ps 3 title "(R_{21}) x (+x2typ)",\
  "out/forTwiss" every :::3::3 u 2:5 lc rgb "blue" pt 7 ps 3 title "(R_{21}) x (-x2typ)"

