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
set map_name "2d_seism" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-006 

##
## load initial data 
##
 
# load points from text file 
pnts_read "2d_seism.xyz" "2d_seism"  
 
##
## construct grid 
##
grid 
 
##
## create gridding rules
##

# resulting surface should tend to be constant or plane 
completer 1 10

# add "resulting surface at points = points values" with weight 
points_add 2 "2d_seism" 

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
surf_save "2d_seism.dat" "2d_seism" 
