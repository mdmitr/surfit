#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_points_exact" 

# set tolerance for cg solver
set tol 1.99526e-006 

##
## load initial data 
##
 
# load points from text file 
pnts_read "points.txt" "points"  
 
##
## construct grid 
##
grid 150 150 
 
##
## create gridding rules
##

# resulting surface at points = points values
points "points" 

# resulting surface should tend to be constant or plane 
completer 1 2  

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
surf_save "points_exact.dat" "map_points_exact" 
