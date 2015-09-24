#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_mask_ineq" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load mask from surfit datafile 
mask_load "data/mask.mask" "test_mask"  
 
# load surface from surfit datafile 
surf_load "data/func.func" "test_func"  
 
##
## construct grid 
##
grid_get -10 10 0.2 -10 10 0.4 
 
##
## create gridding rules
##

# resulting surface >= value where mask is true... 
mask_geq -10 "test_mask"  

# resulting surface = surface values 
surface "test_func" 

# resulting surface should tend to be constant or plane 
completer 

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "mask_ineq.dat" "map_mask_ineq" 

# plot resulting surface in PostScript
surf_plot "mask_ineq.ps" $map_name