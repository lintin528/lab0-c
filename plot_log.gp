reset                                                                           
set xlabel 'x'
set ylabel 'log_2_(x)'
set title 'performance comparison'
set term png enhanced font 'Verdana,10'
set output "log2.png"
set xtic 100
set key left


plot \
"log2.csv" using 1:2 with points pointsize 1 pointtype 1 title "float", \
"log2.csv" using 1:3 with points pointsize 1 pointtype 2 title "fix_16", \
"log2.csv" using 1:4 with points pointsize 1 pointtype 3 title "fix_8", \
"log2.csv" using 1:5 with points pointsize 1 pointtype 4 title "fix_4", \
"log2.csv" using 1:6 with points pointsize 1 pointtype 7 title "fix_2", \