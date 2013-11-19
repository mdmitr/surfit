#
# This script was generated with funner for surfit v3.0

# 
# load plugins
# 
load libsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "3d_seism" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-007

##
## load initial data 
##
 
# load points from text file 
pnts_read "3d_seism.xyz" "3d_seism"  
 
##
## construct grid 
##
grid 25 25
 
##
## create gridding rules
##

# resulting surface should tend to be constant or plane 
completer 

# add "resulting surface at points = points values" with weight 
points_add 5 "3d_seism" 

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
surf_save "3d_seism.dat" "3d_seism" 
