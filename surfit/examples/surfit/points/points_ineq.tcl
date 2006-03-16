#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and functionals
clear_data 

# set name of surface
set map_name "points_ineq" 

# set tolerance for cg solver
set tol 1e-004

##
## load initial data 
##
 
# load points from text file 
pnts_read "points_geq.txt" "points_geq"  
 
# load points from text file 
pnts_read "points_leq.txt" "points_leq"  
 
##
## construct grid 
##
grid 
 
##
## create gridding rules
##

# surface should be greater than or equal to points 
points_geq "points_geq" 

# surface should be lower than or equal to points 
points_leq "points_leq" 

# surface should tend to be constant or plane 
completer 0 1  

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
func_save "points_ineq.dat" 
