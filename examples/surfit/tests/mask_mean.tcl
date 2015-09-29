#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libtclsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_mask_mean" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

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

# resulting surface mean value = value where mask is true... 
mask_mean -2 "test_mask"  

# resulting surface at points = points values 
points "points" 

# resulting surface should tend to be constant or plane 
completer 1 10

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "mask_mean.dat" "map_mask_mean" 

puts [concat "Surface mean value with mask : " [surf_mask_mean "test_mask" "map_mask_mean"]]

# plot resulting surface in PostScript
surf_plot "mask_mean.ps" $map_name