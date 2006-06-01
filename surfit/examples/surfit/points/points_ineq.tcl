#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_points_ineq" 

# set tolerance for cg solver
set tol 1e-004

##
## load initial data 
##
 
# load points from text file 
pnts_read "points_geq.txt" "points_geq"  
 
# load points from text file 
pnts_read "points_leq.txt" "points_leq"  
 
##
## construct grid 
##
grid 
 
##
## create gridding rules
##

# resulting surface should be greater than or equal to points values
points_geq "points_geq" 

# resulting surface should be lower than or equal to points values
points_leq "points_leq" 

# resulting surface should tend to be constant or plane 
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
surf_save "points_ineq.dat" "map_points_ineq" 
