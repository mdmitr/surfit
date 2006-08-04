#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_area_completer" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load points from text file 
pnts_read "11points.txt" "11points"  
 
# load area from text file 
area_read "some_area.txt" "some_area"  
 
##
## construct grid 
##
grid 
 
##
## create gridding rules
##

# resulting surface at points = points values 
points "11points" 

# resulting surface should tend to be constant or plane inside(outside) area 
area_completer "some_area" 1 2 30 2 1 

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
surf_save "map_area_completer.dat" "map_area_completer" 
