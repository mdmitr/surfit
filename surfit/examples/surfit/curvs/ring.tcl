#
load libsurfit[info sharedlibextension]

# removing all previous data and functionals
clear_data

# setting map name for calculating surfit
set map_name map_ring

# set tolerance for cg solver
set tol 5e-6

##
## loading initial data 
##
area_read_bln ring.bln ring

##
## constructing grid
##
grid_get -12 12 0.2 -12 12 0.2

##
## constructing functionals sequence
##
area 20 ring 0
area 30 ring 

##
## runing cmofs algorithm
##
cmofs

##
## saving results
##
grid_unload
file_save ring.dat
