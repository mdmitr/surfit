#
load libsurfit[info sharedlibextension]

# removing all previous data and functionals
clear_data

# setting map name for calculating surfit
set map_name map_trend

# set tolerance for cg solver
set tol 1e-5

##
## loading initial data 
##
pnts_read 7points.txt 7points

# reading fault line from 2-column text file
curv_read 1fault.txt 1fault
curv_read 1fault2.txt 1fault2

# reading surfit_func from binary ROFF file
func_load func.func
func_setName trend


##
## constructing grid
##
grid_get -10 10 0.2 -10 10 0.2

##
## constructing functionals sequence
##
points

trend 0.2 1
fault_add 1fault
fault_add 1fault2

##
## runing cmofs algorithm
##
cmofs

##
## saving results
##

grid_unload
file_save trend.dat
