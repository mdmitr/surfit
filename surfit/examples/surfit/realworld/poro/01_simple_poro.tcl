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
set map_name "simple_poro" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-006 

##
## load initial data 
##
 
# load points from text file 
pnts_read "kpor.txt" "kpor"  
 
##
## construct grid 
##
grid_get 8000 14000 25 24500 30500 25 
 
##
## create gridding rules
##

# resulting surface at points = points values 
points "kpor" 

# resulting surface should tend to be constant or plane 
completer 1 5

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
surf_save "simple_poro.dat" "simple_poro" 
