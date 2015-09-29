#
# This script was generated with funner for surfit v3.0

# 
# load plugins
# 
load libtclsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "eff_thickness" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-006 

##
## load initial data 
##
 
# load points from text file 
pnts_read "eff_thickness.txt" "eff_thickness"  
 
# load surface from surfit datafile 
surf_load "thickness_surface.dat" "thickness_surface"  
 
##
## construct grid 
##
grid_get 51000 62000 25 52000 66000 25
 
##
## create gridding rules
##

# resulting surface >= value... 
geq 0  

# resulting surface <= surface values 
surface_leq "thickness_surface" 

# resulting surface at points = points values 
points "eff_thickness" 

# resulting surface should tend to be constant or plane 
completer 1 10 

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# unload grid from memory
grid_unload 

# save surface to surfit datafile 
surf_save "eff_thickness.dat" "eff_thickness" 
