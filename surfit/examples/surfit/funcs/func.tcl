#
load libsurfit[info sharedlibextension]

# removing all previous data and functionals
clear_data

# setting map name for calculating surfit
set map_name map_func

# set tolerance for cg solver
set tol 1e-5

##
## loading initial data 
##
func_load func.func

##
## constructing grid
##
grid_get -10 10 0.2 -10 10 0.4

##
## constructing functionals sequence
##
func 
completer 2 1

##
## runing cmofs algorithm
##
cmofs

##
## saving results
##
grid_unload
func_del 0
file_save func.dat
