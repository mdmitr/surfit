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
surf_load func.func
# convering func to defarea
surf_to_mask 0 60
mask_not
surf_load func.func

##
## constructing grid
##
grid_get -10 10 0.2 -10 10 0.4

##
## constructing functionals sequence
##
mask undef
surface
completer 1 2

##
## runing cmofs algorithm
##
surfit

##
## saving results
##

grid_unload
surf_del 0
surf_save mask.dat map_mask
