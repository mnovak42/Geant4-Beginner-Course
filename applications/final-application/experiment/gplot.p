################################################################################
# Gnuplot script to compare the experimental and simulated energy deposit 
# distributions when 100 [MeV] electrons hit a 5.6 [um] thin silicon target.
# It is assumed, that this script is used in the same directory where the 
# experimental data ("exp_Meroli_100MeV_electron_5p6um_Si.dat") and the result 
# of the MC simulation ("Hist_Edep.dat") is located. It can be used as the input 
# of the 'gnuplot' program: gnuplot glopt.p
# It will produce a figure "fig_Meroli_100MeV_electron_5p6um_Si.eps" in .eps 
# format that might be converted to pdf using e.g. the 'epstopdf' program as: 
# epstopdf fig_Meroli_100MeV_electron_5p6um_Si.eps
################################################################################ 
#
set term postscript eps enhanced color dl 1.1 "Times" 22
######## Output File Name
set output "fig_Meroli_100MeV_electron_5p6um_Si.eps"
######## Set the title
set title "Distribution of energy lost by E_0=100 [MeV] e^- in 5.6 [{/Symbol m}m]"
######## Line types 
set style line 1 lt 1 pt 7 lw 3 lc rgb 'blue' 
set style line 2 lt 1 pt 6 lw 3 lc rgb 'red'
######## Set tics and range
set mxtics 5
set xrange[0:6]
######## Labels
set ylabel "Energy loss distribution [arb.units]"
set xlabel "Energy loss [keV]"
######## Grid
set grid mxtics xtics lw 1.5 lc rgb 'black', lw 1.5 lc rgb 'gray'
set grid mytics ytics lw 1.5 lc rgb 'black', lw 1.5 lc rgb 'gray'
######## Set key box
set key box reverse Left w -8
######## Plot
## NOTE: 
## - energy is in [MeV] in the simulation while [keV] in the exp. => x 1000.0 
## - the experimental distribution is in arbitrary units => scaling x 6.4 
plot "exp_Meroli_100MeV_electron_5p6um_Si.dat" u 1:2 w p ls 1 title "Exp. (Meroli et al. 2011)",\
     "Hist_Edep.dat" u ($2*1000.0):($3*6.4) w l ls 2 title "MC (Geant4 EMZ)"
