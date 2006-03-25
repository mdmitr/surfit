#
load libsurfit[info sharedlibextension]

# removing all previous data and functionals
clear_data

# setting map name for calculating surfit
set map_name map_ineq

# set tolerance for cg solver
set tol 1e-5

##
## loading initial data 
##
pnts_read 7points.txt 7points

##
## constructing grid
##
grid

##
## constructing functionals sequence
##
geq 80
leq 120
points 7points
completer 1 2

##
## runing cmofs algorithm
##
surfit

set minz [surf_minz]
puts "Surface minimum value: $minz"

set maxz [surf_maxz]
puts "Surface maximum value: $maxz"

##
## saving results
##
grid_unload
file_save ineq.dat