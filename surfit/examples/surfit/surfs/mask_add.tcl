#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_mask_add" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load mask from surfit datafile 
mask_load "mask.mask" "test_mask"  
 
# load surface from surfit datafile 
surf_load "func.func" "test_func"  
 
##
## construct grid 
##
grid_get -10 10 0.2 -10 10 0.4 
 
##
## create gridding rules
##

# resulting surface = surface values 
surface "test_func" 

# add "resulting surface where mask is true = value..." with weight 
mask_add 0.2 3 "test_mask"  

# resulting surface should tend to be constant or plane 
completer 

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
surf_save "mask_add.dat" "map_mask_add" 
