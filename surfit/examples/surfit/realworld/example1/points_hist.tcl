#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_points_hist" 

# set tolerance for cg solver
set tol 1e-007

##
## load initial data 
##
 
# load points from text file 
pnts_read "points.txt" "points"  

hist_read "hist.txt" 1548.97 1749.34
hist_write "hist_src.txt"
 
##
## construct grid 
##
grid 50 50
 
##
## create gridding rules
##

# resulting surface at points = points values
points

#historgram of resulting surface = desired histogram
hist

# resulting surface should tend to be constant or plane 
completer 0 1  

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "points_hist.dat" "map_points_hist" 

# plot resulting surface in EPS
surf_plot "points_hist.eps" "map_points_hist" 

hist_del
hist_from_surf "map_points_hist" 10 
hist_write "hist_result.txt"
