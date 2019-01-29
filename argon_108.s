make dirR=/home/jespinoz/P1.8_ljmd  -C Obj-serial libLJMD
make[1]: Entering directory `/home/jespinoz/P1.8_ljmd/Obj-serial'
gcc -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer -I/home/jespinoz/P1.8_ljmd/include -DMORSE -DTHIRD_LAW -c -fPIC /home/jespinoz/P1.8_ljmd/src/velverlet_time_integration.c -o /home/jespinoz/P1.8_ljmd/Obj-serial/velverlet_time_integration.o
gcc -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer -I/home/jespinoz/P1.8_ljmd/include -DMORSE -DTHIRD_LAW -c -fPIC /home/jespinoz/P1.8_ljmd/src/output.c -o /home/jespinoz/P1.8_ljmd/Obj-serial/output.o
gcc -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer -I/home/jespinoz/P1.8_ljmd/include -DMORSE -DTHIRD_LAW -c -fPIC /home/jespinoz/P1.8_ljmd/src/input.c -o /home/jespinoz/P1.8_ljmd/Obj-serial/input.o
gcc -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer -I/home/jespinoz/P1.8_ljmd/include -DMORSE -DTHIRD_LAW -c -fPIC /home/jespinoz/P1.8_ljmd/src/compute_force.c -o /home/jespinoz/P1.8_ljmd/Obj-serial/compute_force.o
gcc -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer -I/home/jespinoz/P1.8_ljmd/include -DMORSE -DTHIRD_LAW -c -fPIC /home/jespinoz/P1.8_ljmd/src/data_structure.c -o /home/jespinoz/P1.8_ljmd/Obj-serial/data_structure.o
gcc -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer -I/home/jespinoz/P1.8_ljmd/include -DMORSE -DTHIRD_LAW -c -fPIC /home/jespinoz/P1.8_ljmd/src/utilities_ljmd.c -o /home/jespinoz/P1.8_ljmd/Obj-serial/utilities_ljmd.o
gcc  -shared -o /home/jespinoz/P1.8_ljmd/Obj-serial/libLJMD.so /home/jespinoz/P1.8_ljmd/Obj-serial/velverlet_time_integration.o /home/jespinoz/P1.8_ljmd/Obj-serial/output.o /home/jespinoz/P1.8_ljmd/Obj-serial/input.o /home/jespinoz/P1.8_ljmd/Obj-serial/compute_force.o /home/jespinoz/P1.8_ljmd/Obj-serial/data_structure.o /home/jespinoz/P1.8_ljmd/Obj-serial/utilities_ljmd.o
make[1]: Leaving directory `/home/jespinoz/P1.8_ljmd/Obj-serial'
make dirR=/home/jespinoz/P1.8_ljmd dirEXE=/home/jespinoz/P1.8_ljmd  -C Obj-serial
make[1]: Entering directory `/home/jespinoz/P1.8_ljmd/Obj-serial'
gcc -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer -I/home/jespinoz/P1.8_ljmd/include -DMORSE -DTHIRD_LAW -c -fPIC /home/jespinoz/P1.8_ljmd/src/ljmd.c -o /home/jespinoz/P1.8_ljmd/Obj-serial/ljmd.o
gcc  -shared -o /home/jespinoz/P1.8_ljmd/Obj-serial/libLJMD.so /home/jespinoz/P1.8_ljmd/Obj-serial/velverlet_time_integration.o /home/jespinoz/P1.8_ljmd/Obj-serial/output.o /home/jespinoz/P1.8_ljmd/Obj-serial/input.o /home/jespinoz/P1.8_ljmd/Obj-serial/compute_force.o /home/jespinoz/P1.8_ljmd/Obj-serial/data_structure.o /home/jespinoz/P1.8_ljmd/Obj-serial/utilities_ljmd.o
gcc -o /home/jespinoz/P1.8_ljmd/ljmd-serial.x /home/jespinoz/P1.8_ljmd/Obj-serial/ljmd.o -lm -Wl,-rpath,/home/jespinoz/P1.8_ljmd/Obj-serial -L/home/jespinoz/P1.8_ljmd/Obj-serial -lLJMD 
make[1]: Leaving directory `/home/jespinoz/P1.8_ljmd/Obj-serial'
make  -C examples check
make[1]: Entering directory `/home/jespinoz/P1.8_ljmd/examples'
../ljmd-serial.x < argon_108.inp
Starting simulation with 108 atoms for 10000 steps.
     NFI            TEMP            EKIN                 EPOT              ETOT
       0          72.64160016          23.16879686          -0.00101024          23.16778662
     100         188.54912588          60.13711684          -0.04674970          60.09036714
     200         295.70351955          94.31365445          -0.67631410          93.63734035
     300         341.69130158         108.98130464          -0.65354226         108.32776238
     400         350.14506348         111.67760389          -1.10039036         110.57721353
     500         344.05761764         109.73603327          -0.85858373         108.87744954
     600         358.99642082         114.50071488          -0.90978561         113.59092927
     700         368.86834330         117.64933174          -1.15810862         116.49122312
     800         373.47316143         119.11802317          -1.33436075         117.78366242
     900         337.91443030         107.77668410          -1.11633607         106.66034802
    1000         341.12800868         108.80164424          -1.03032647         107.77131777
    1100         368.51798740         117.53758689          -0.91837032         116.61921656
    1200         374.71614895         119.51446991          -0.65023242         118.86423749
    1300         391.12646893         124.74848691          -1.69649481         123.05199210
    1400         377.70110301         120.46651108          -0.68337217         119.78313891
    1500         368.14607254         117.41896588          -0.90436872         116.51459716
    1600         376.38022662         120.04522195          -1.19760804         118.84761391
    1700         393.97971462         125.65852013          -1.05499663         124.60352350
    1800         406.54069788         129.66480398          -1.48758891         128.17721508
    1900         430.94383601         137.44810376          -1.67985962         135.76824414
    2000         434.77408144         138.66974780          -1.47250324         137.19724456
    2100         374.94080516         119.58612326          -0.76039408         118.82572918
    2200         338.16635274         107.85703392          -0.77551588         107.08151805
    2300         368.82146323         117.63437950          -1.17019308         116.46418642
    2400         417.56420253         133.18071414          -1.14857714         132.03213700
    2500         384.62963414         122.67634305          -1.27722399         121.39911906
    2600         403.66454809         128.74746557          -1.47665742         127.27080815
    2700         407.39742813         129.93805525          -1.42920140         128.50885385
    2800         378.53574048         120.73271593          -0.91004283         119.82267309
    2900         352.23016483         112.34264003          -1.00033593         111.34230410
    3000         339.30624314         108.22059817          -1.37204377         106.84855441
    3100         353.78473147         112.83846389          -1.16406094         111.67440295
    3200         398.53368958         127.11099531          -1.80677383         125.30422147
    3300         367.27215793         117.14023372          -0.70982114         116.43041258
    3400         355.92908856         113.52239946          -0.90977149         112.61262796
    3500         366.68810359         116.95395153          -1.04368244         115.91026909
    3600         357.75194934         114.10379484          -0.64759643         113.45619841
    3700         334.18666132         106.58772457          -0.56683027         106.02089431
    3800         344.70195756         109.94154335          -1.00877133         108.93277202
    3900         342.02424634         109.08749626          -0.72840540         108.35909086
    4000         360.80519577         115.07761764          -0.78363448         114.29398316
    4100         382.10188207         121.87012493          -0.82750178         121.04262315
    4200         342.27418013         109.16721181          -0.49751435         108.66969746
    4300         352.34979043         112.38079422          -0.63889026         111.74190396
    4400         355.69939692         113.44914007          -1.21860301         112.23053706
    4500         345.47576884         110.18834789          -1.45087320         108.73747469
    4600         357.46132759         114.01110200          -0.98849086         113.02261114
    4700         353.71136758         112.81506472          -1.17289831         111.64216642
    4800         373.09163459         118.99633645          -1.79958414         117.19675232
    4900         393.61491996         125.54217009          -1.57153355         123.97063654
    5000         421.86752436         134.55324433          -1.66689704         132.88634729
    5100         438.75999179         139.94104066          -1.47645780         138.46458286
    5200         408.38740724         130.25380580          -1.55095553         128.70285027
    5300         384.16417609         122.52788675          -1.17855786         121.34932889
    5400         392.11486176         125.06373151          -1.12302994         123.94070158
    5500         404.11174526         128.89009762          -0.86148246         128.02861516
    5600         366.96299554         117.04162741          -0.78924675         116.25238065
    5700         355.71254660         113.45333412          -0.86890936         112.58442476
    5800         409.33861115         130.55718912          -1.65762588         128.89956324
    5900         396.64010702         126.50704344          -0.95175195         125.55529149
    6000         370.02556779         118.01842464          -1.63758492         116.38083972
    6100         358.29359027         114.27654942          -0.89924571         113.37730371
    6200         370.75807717         118.25205607          -0.65303774         117.59901833
    6300         361.13925766         115.18416557          -0.84150581         114.34265976
    6400         397.46382045         126.76976411          -1.61495431         125.15480980
    6500         415.79379889         132.61604979          -1.24810626         131.36794353
    6600         370.91058072         118.30069657          -1.31367843         116.98701814
    6700         359.43303412         114.63997124          -0.75618070         113.88379054
    6800         408.82855787         130.39450932          -1.04026235         129.35424698
    6900         364.35007091         116.20824378          -0.80852956         115.39971422
    7000         377.15708711         120.29299902          -0.79643147         119.49656755
    7100         384.40004648         122.60311683          -1.04502754         121.55808929
    7200         385.00096221         122.79477690          -1.18030813         121.61446878
    7300         334.19418571         106.59012445          -0.51789128         106.07223318
    7400         316.08495650         100.81424600          -0.82065065          99.99359536
    7500         330.61556475         105.44873520          -0.39413782         105.05459737
    7600         298.97445782          95.35690934          -0.53779165          94.81911768
    7700         324.05231760         103.35540934          -1.10978036         102.24562898
    7800         344.73019178         109.95054856          -0.98385577         108.96669279
    7900         341.13786830         108.80478893          -0.98529045         107.81949848
    8000         332.47427977         106.04156617          -0.63649825         105.40506792
    8100         339.91932098         108.41613731          -0.81912631         107.59701100
    8200         329.35964806         105.04816474          -0.75133030         104.29683444
    8300         362.66330888         115.67025664          -1.13116753         114.53908911
    8400         359.83723621         114.76889016          -1.58095826         113.18793189
    8500         374.77942122         119.53465039          -1.39652782         118.13812257
    8600         377.65942933         120.45321940          -1.14727805         119.30594134
    8700         331.40683964         105.70110969          -1.39952618         104.30158352
    8800         344.39228905         109.84277561          -0.88575615         108.95701946
    8900         367.71161788         117.28039801          -1.19391497         116.08648304
    9000         385.06834617         122.81626879          -1.02428586         121.79198294
    9100         439.65810949         140.22749231          -1.81396614         138.41352617
    9200         406.11525042         129.52910893          -1.04330982         128.48579911
    9300         384.54702906         122.64999643          -1.06334131         121.58665512
    9400         415.41925630         132.49659067          -1.09472283         131.40186784
    9500         387.90880821         123.72222472          -0.77425719         122.94796753
    9600         394.15605530         125.71476341          -1.37369981         124.34106360
    9700         382.78855313         122.08913638          -1.17117451         120.91796187
    9800         388.95113491         124.05467135          -0.93370145         123.12096990
    9900         389.66914397         124.28367796          -1.45130758         122.83237038
   10000         380.47195612         121.35026547          -1.15540882         120.19485665
Simulation Done.
head -10 argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> a.dat
head -10 ../reference/argon_108.dat | awk '{printf("%d %.6f %.6f %.6f\n",$1,$2,$3,$4);}'> b.dat
cmp a.dat b.dat || exit 1
a.dat b.dat differ: char 24, line 1
make[1]: Leaving directory `/home/jespinoz/P1.8_ljmd/examples'
