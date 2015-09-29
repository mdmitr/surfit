#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libtclsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_points_approx" 

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
grid 50 50 
 
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

# save surface to surfit datafile 
surf_save "points_approx.dat" "map_points_approx" 

# plot resulting surface in PostScript
surf_plot "points_approx.ps" "map_points_approx" 