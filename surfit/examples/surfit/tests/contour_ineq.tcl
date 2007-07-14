#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_cntr_ineq" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load contour from text file 
cntr_read "data/cntr_big_circle2.xyz" "cntr_big_circle2"  
 
# load contour from text file 
cntr_read "data/cntr_big_circle.xyz" "cntr_big_circle"  
 
# load contour from text file 
cntr_read "data/cntr_center2.xyz" "cntr_center2"  
 
# load contour from text file 
cntr_read "data/cntr_center.xyz" "cntr_center"  
 
# load contour from text file 
cntr_read "data/cntr_small_circle2.xyz" "cntr_small_circle2"  
 
# load contour from text file 
cntr_read "data/cntr_small_circle.xyz" "cntr_small_circle"  
 
##
## construct grid 
##
grid_get -1000 1000 20 -1000 1000 20 
 
##
## create gridding rules
##

# resulting surface at contour >= contour values 
contour_geq "cntr_big_circle" 

# resulting surface at contour <= contour values 
contour_leq "cntr_big_circle2" 

# resulting surface at contour >= contour values 
contour_geq "cntr_center" 

# resulting surface at contour <= contour values 
contour_leq "cntr_center2" 

# resulting surface at contour >= contour values 
contour_geq "cntr_small_circle" 

# resulting surface at contour <= contour values 
contour_leq "cntr_small_circle2" 

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
surf_save "contour_ineq.dat" "map_cntr_ineq" 

# plot resulting surface in EPS
surf_plot "contour_ineq.eps" $map_name