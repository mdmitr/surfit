#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and functionals
clear_data 

# set name of surface
set map_name "points_approx" 

# set tolerance for cg solver
set tol 1e-006 

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

# resulting surface should tend to be constant or plane 
completer 1 2  

# add "resulting surface at points = points values" with weight 
points_add 0.6 "points" 

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
surf_save "points_approx.dat" 
