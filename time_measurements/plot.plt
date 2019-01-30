set terminal png size 800, 600      
set output  "time_profiling.png" 
set title "Elapsed time for different optimizations"
set ylabel "Elapsed time (s)"
set style line 1 lc rgb "red"
set style line 2 lc rgb "blue"
set style line 3 lc rgb "green"
unset key

set style fill solid
set boxwidth 0.5
set yrange [0:0.04]

plot "time.dat" every ::0::0 using 1:3:xtic(2) with boxes ls 1,\
	 "time.dat" every ::1::1 using 1:3:xtic(2) with boxes ls 1,\
	 "time.dat" every ::2::2 using 1:3:xtic(2) with boxes ls 1,\
	 "time.dat" every ::3::3 using 1:3:xtic(2) with boxes ls 1,\
	 "time.dat" every ::4::4 using 1:3:xtic(2) with boxes ls 2,\
	 "time.dat" every ::5::5 using 1:3:xtic(2) with boxes ls 2,\
	 "time.dat" every ::6::6 using 1:3:xtic(2) with boxes ls 2,\
	 "time.dat" every ::7::7 using 1:3:xtic(2) with boxes ls 3
