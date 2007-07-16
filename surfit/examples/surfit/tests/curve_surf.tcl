#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_curv_surf" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load curve from text file 
curv_read "data/spiral.xy" "spiral"  
 
# load curve from text file 
curv_read "data/spiral2.xy" "spiral2"  
 
# load surface from surfit datafile 
surf_load "data/func.func" "test_func"  
 
##
## construct grid 
##
grid 
 
##
## create gridding rules
##

# resulting surface at curve = surface values... 
curve_surf "test_func" "spiral"  

# resulting surface should tend to be constant or plane 
completer 

# add "resulting surface at curve = surface values..." with weight 
curve_surf_add "test_func" 0.5 "spiral2"  

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "curve_surf.dat" "map_curv_surf" 

# plot resulting surface in PostScript
surf_plot "curve_surf.ps" $map_name