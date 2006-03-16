#
load libsurfit[info sharedlibextension]

# removing all previous data and functionals
clear_data

# setting map name for calculating surfit
set map_name map_mask

# set tolerance for cg solver
set tol 1e-5

##
## loading initial data 
##
func_load func.func
# convering func to defarea
func_to_mask 0 60
mask_not
func_load func.func

##
## constructing grid
##
grid_get -10 10 0.2 -10 10 0.4

##
## constructing functionals sequence
##
mask undef
func
completer 1 2

##
## runing cmofs algorithm
##
cmofs

##
## saving results
##

grid_unload
func_del 0
func_save mask.dat map_mask
