#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and functionals
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
cntr_read "cntr_small_circle.xyz" "cntr_small_circle"  
 
# load contour from text file 
cntr_read "cntr1.xyz" "cntr1"  
 
# load contour from text file 
cntr_read "cntr2.xyz" "cntr2"  
 
# load contour from text file 
cntr_read "cntr_big_circle.xyz" "cntr_big_circle"  
 
# load contour from text file 
cntr_read "cntr_center.xyz" "cntr_center"  
 
##
## construct grid 
##
grid_get -1000 1000 20 -1000 1000 20 
 
##
## create gridding rules
##

# surface at contour = contour values 
contour "cntr_small_circle" 

# surface at contour = contour values 
contour "cntr_center" 

# surface at contour <= contour values 
contour_leq "cntr1" 

# surface at contour >= contour values 
contour_geq "cntr2" 

# surface should tend to be constant or plane 
completer 

# add "surface at contour = contour values" with weight 
contour_add 0.5 "cntr_big_circle" 

##
## run cmofs algorithm
##
cmofs 

##
## save results 
##

# unload grid from memory
grid_unload 

# saves function to ROFF file 
func_save "contour.dat" 
