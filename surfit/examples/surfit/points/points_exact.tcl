#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and functionals
clear_data 

# set name of surface
set map_name "points_exact" 

# set tolerance for cg solver
set tol 1.99526e-006 

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

# approximate points 
points "points" 

# surface should tend to be constant or plane 
completer 1 2  

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
func_save "points_exact.dat" 
