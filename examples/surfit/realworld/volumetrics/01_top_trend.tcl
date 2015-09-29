#
# This script was generated with funner for surfit v3.0

# 
# load plugins
# 
load libtclsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "top_trend" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-007 

##
## load initial data 
##
 
# load curve from text file 
curv_read "isos/*.xyz" 

curv_to_cntr 2160 "iso_2160*"
curv_to_cntr 2170 "iso_2170*"
curv_to_cntr 2180 "iso_2180*"
curv_to_cntr 2190 "iso_2190*"
curv_to_cntr 2200 "iso_2200*"
curv_to_cntr 2210 "iso_2210*"
curv_to_cntr 2220 "iso_2220*"
curv_to_cntr 2230 "iso_2230*"
curv_to_cntr 2240 "iso_2240*"
 
##
## construct grid 
##
grid_get 51000 62000 25 52000 66000 25
 
##
## create gridding rules
##

# resulting surface at points = points values 
#points "aoup" 

smooth_contour *

# resulting surface should tend to be constant or plane 
completer 1 15

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
surf_save "top_trend.dat" "top_trend" 
