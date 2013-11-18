#
# This script was generated with funner for surfit v3.0

# 
# load plugins
# 
load libsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "top_surface" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-007

##
## load initial data 
##
 
# load points from text file 
pnts_read "top_tvd.txt" "top_tvd"  
 
# load surface from surfit datafile 
surf_load "top_trend.dat" "top_trend"  
 
##
## construct grid 
##
grid_get 51000 62000 25 52000 66000 25
 
##
## create gridding rules
##

# resulting surface at points = points values 
points "top_tvd" 

# resulting surface looks like trend surface 
trend 1 2 "top_trend" 

# resulting surface should tend to be constant or plane 
completer 

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
surf_save "top_surface.dat" "top_surface" 

surf_trace_cntr "top_surface" 2187 2187
cntr_to_curv *

curv_setName ext_woc top_surface_2187
curv_setName ext_woc2 top_surface_2187_2
curv_setName ext_woc3 top_surface_2187_3
file delete "ext_woc.bln"
curv_save_bln "ext_woc.bln" "*" 

