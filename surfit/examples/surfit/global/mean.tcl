#
load libsurfit[info sharedlibextension]

# removing all previous data and functionals
clear_data

# setting map name for calculating surfit
set map_name map_mean

# set tolerance for cg solver
set tol 1e-5

##
## loading initial data 
##
pnts_read 7points.txt 7points

##
## constructing grid
##
grid_get -10 10 0.2 -10 10 0.2

##
## constructing functionals sequence
##
points
mean 30
completer 1 2

##
## runing cmofs algorithm
##
surfit

##
## saving results
##

grid_unload
file_save mean.dat

set mean_value [surf_mean map_mean]
puts "surface mean value is $mean_value"
