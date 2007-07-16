#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_points_triangulate" 

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

# resulting surface at points = points values
points "points" 

triangulate 
completer_add 0.1 1 5

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "points_triangulate.dat" $map_name

# plot resulting surface in PostScript
surf_plot "ponts_triangulate.ps" $map_name