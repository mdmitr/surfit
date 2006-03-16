#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and functionals
clear_data 

# set name of surface
set map_name "points_approx" 

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
grid 150 150 
 
##
## create gridding rules
##

# surface should tend to be constant or plane 
completer 1 2  

# add "approximate points" with weight 
points_add 0.6 "points" 

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
func_save "points_approx.dat" 
