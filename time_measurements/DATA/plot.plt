set terminal png size 800, 600      
set output  "time_profiling_LJ.png" 
set title "Elapsed time for different optimizations for Leonard-Johnson Potential"
set ylabel "Elapsed time (s)"
set style line 1 lc rgb "red"
set style line 2 lc rgb "blue"
set style line 3 lc rgb "green"
unset key

set style fill solid
set boxwidth 0.5
set yrange [0:200]

plot "time_LJ.dat" every ::0::0 using 1:3:xtic(2) with boxes ls 1, '' u 1:($3 + 3):($3) with labels,\
	 "time_LJ.dat" every ::1::1 using 1:3:xtic(2) with boxes ls 1,\
	 "time_LJ.dat" every ::2::2 using 1:3:xtic(2) with boxes ls 2,\
	 "time_LJ.dat" every ::3::3 using 1:3:xtic(2) with boxes ls 2,\
	 "time_LJ.dat" every ::4::4 using 1:3:xtic(2) with boxes ls 3,\
	 "time_LJ.dat" every ::5::5 using 1:3:xtic(2) with boxes ls 3


set terminal png size 800, 600      
set output  "time_profiling_MS.png" 
set title "Elapsed time for different optimizations for Morse Potential"
set ylabel "Elapsed time (s)"
set style line 1 lc rgb "red"
set style line 2 lc rgb "blue"
set style line 3 lc rgb "green"
unset key

set style fill solid
set boxwidth 0.5
set yrange [0:200]

plot "time_MS.dat" every ::0::0 using 1:3:xtic(2) with boxes ls 1, '' u 1:($3 +3):($3) with labels,\
	 "time_MS.dat" every ::1::1 using 1:3:xtic(2) with boxes ls 1,\
	 "time_MS.dat" every ::2::2 using 1:3:xtic(2) with boxes ls 2,\
	 "time_MS.dat" every ::3::3 using 1:3:xtic(2) with boxes ls 3,\
	 "time_MS.dat" every ::4::4 using 1:3:xtic(2) with boxes ls 3
