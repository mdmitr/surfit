#
load libsurfit[info sharedlibextension]

# removing all previous data and functionals
clear_data

# setting map name for calculating surfit
set map_name map_wmean

# set tolerance for cg solver
set tol 1e-5

##
## loading initial data 
##
pnts_read 7points.txt 7points
func_load func.func test_func

##
## constructing grid
##
grid_get -10 10 0.2 -10 10 0.2

##
## constructing functionals sequence
##
points
wmean 30 test_func 
completer 1 2

##
## runing cmofs algorithm
##
cmofs

##
## saving results
##

grid_unload
file_save wmean.dat

set mean_value [func_wmean test_func map_wmean]
puts "func weighted mean value is $mean_value"
