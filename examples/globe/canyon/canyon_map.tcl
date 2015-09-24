#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libglobe[info sharedlibextension]
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_canyon" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-006 

##
## load initial data 
##
 
# load surface from surfit datafile 
surf_load "canyon_trend.dat" "canyon_trend"  
 
# load points from surfit datafile 
pnts_load "canyon_pnts.dat" "canyon_pnts"  
 
##
## construct grid 
##
grid_get -114 -111.6 0.0006 35.6 37 0.0007 
 
##
## create gridding rules
##

# resulting surface at points = points values 
points "canyon_pnts" 

# resulting surface looks like trend surface 
trend 1 2 "canyon_trend" 

completer 0 1

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
surf_save "map_canyon.dat" "map_canyon" 
