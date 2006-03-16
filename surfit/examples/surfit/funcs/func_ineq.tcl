#
load libsurfit[info sharedlibextension]

# removing all previous data and functionals
clear_data

# setting map name for calculating surfit
set map_name map_func_ineq

# set tolerance for cg solver
set tol 1e-5

##
## loading initial data 
##
func_load func.func test_func
func_plus_value 80
pnts_read 7points.txt 7points

##
## constructing grid
##
grid_get -10 10 0.2 -10 10 0.4

##
## constructing functionals sequence
##
func_geq test_func
points 7points
completer 2 1

##
## runing cmofs algorithm
##
cmofs

##
## saving results
##
grid_unload
file_save func_ineq.dat
