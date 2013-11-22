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
set map_name "top_tvd" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-007

##
## load initial data 
##
 
# load points from text file 
pnts_read "top_tvd.xyz" "top_tvd"  

# load surface from surfit datafile 
surf_load "3d_seism.dat" "3d_seism"  

# load surface from surfit datafile 
surf_load "2d_seism.dat" "2d_seism"  


##
## construct grid 
##
grid 25 25 
 

##
## create gridding rules
##

# resulting surface at points = points values 
points "top_tvd" 

# resulting surface should tend to be constant or plane 
completer 1 5

# resulting surface looks like trend surface 
trend_add 7 1 2 "3d_seism" 

# resulting surface looks like trend surface 
trend_add 2 0 1 "2d_seism" 

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
surf_save "top_tvd.dat" "top_tvd" 
