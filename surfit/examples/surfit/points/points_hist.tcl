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

#hist_from_pnts "points" 10
#hist_write "sou_hist.txt"
#hist_delall
hist_read "hist.txt" 1548.97 1749.34
 
##
## construct grid 
##
grid  150 150
 
##
## create gridding rules
##
points
hist "hist"
# resulting surface at points = points values




# resulting surface should tend to be constant or plane 
completer 1 20  
#points_add 75 "points" 
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
surf_save "points_hist.dat" "map_points_hist" 

hist_del
hist_from_surf "map_points_hist" 10 
hist_write "res_hist.txt"
