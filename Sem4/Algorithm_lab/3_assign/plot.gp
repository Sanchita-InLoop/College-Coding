# General Settings
set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set grid
set key outside top right
set xlabel "Percentage of Duplicates (%)"
set xtics (10, 50, 90)
set xrange [0:100]

# --- GRAPH 1: EXECUTION TIME ---
set output "Graph_Time.png"
set title "Impact of Duplicates on Execution Time"
set ylabel "Execution Time (seconds)"
plot "results.dat" using 1:2 title "Standard Quicksort" with linespoints lw 2 pt 7 lc rgb "red", \
     "results.dat" using 1:3 title "Randomized Quicksort" with linespoints lw 2 pt 5 lc rgb "blue"

# --- GRAPH 2: COMPARISONS ---
set output "Graph_Comparisons.png"
set title "Impact of Duplicates on Key Comparisons"
set ylabel "Number of Comparisons"
set format y "%.1e"  # Scientific notation for large numbers
plot "results.dat" using 1:4 title "Standard Quicksort" with linespoints lw 2 pt 7 lc rgb "red", \
     "results.dat" using 1:5 title "Randomized Quicksort" with linespoints lw 2 pt 5 lc rgb "blue"

# --- GRAPH 3: RECURSION DEPTH ---
set output "Graph_Depth.png"
set title "Impact of Duplicates on Recursion Depth"
set ylabel "Maximum Recursion Depth"
set format y "%g"
plot "results.dat" using 1:6 title "Standard Quicksort" with linespoints lw 2 pt 7 lc rgb "red", \
     "results.dat" using 1:7 title "Randomized Quicksort" with linespoints lw 2 pt 5 lc rgb "blue"