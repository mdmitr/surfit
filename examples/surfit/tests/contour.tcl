#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libtclsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_cntr" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load contour from text file 
cntr_read "data/cntr_small_circle.xyz" "cntr_small_circle"  
 
# load contour from text file 
cntr_read "data/cntr_big_circle.xyz" "cntr_big_circle"  
 
# load contour from text file 
cntr_read "data/cntr_center.xyz" "cntr_center"  
 
##
## construct grid 
##
grid_get -1000 1000 20 -1000 1000 20 
 
##
## create gridding rules
##

# resulting surface at contour = contour values 
contour "cntr_small_circle" 

# resulting surface at contour = contour values 
contour "cntr_center" 

# resulting surface should tend to be constant or plane 
completer 

# add "resulting surface at contour = contour values" with weight 
contour_add 0.5 "cntr_big_circle" 

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "contour.dat" "map_cntr" 

# plot resulting surface in PostScript
surf_plot "contour.ps" $map_name