#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_mask_completer" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-007 

##
## load initial data 
##
 
# load points from text file 
pnts_read "data/points.txt" "points"  
 
# load mask from surfit datafile 
mask_load "data/mask.mask" "test_mask"  
 
##
## construct grid 
##
grid_get -10 10 0.2 -10 10 0.4 
 
##
## create gridding rules
##

# resulting surface at points = points values 
points "points" 

# resulting surface should tend to be constant or plane where mask is true 
mask_completer "test_mask" 1 2 30 2  

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
surf_save "mask_completer.dat" "map_mask_completer" 

# plot resulting surface in PostScript
surf_plot "mask_completer.ps" $map_name