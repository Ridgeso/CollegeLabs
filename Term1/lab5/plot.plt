set term png
set view map
set pm3d interpolate 4,4
set out ’vec_NUMER.png’
splot ’dane.dat’ u 1:2:NUMER w pm3d