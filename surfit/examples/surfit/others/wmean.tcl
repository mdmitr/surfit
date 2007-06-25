#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_wmean" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-006
##
## load initial data 
##
 
# load points from text file 
pnts_read "7points.txt" "7points"  
 
# load surface from surfit datafile 
surf_load "func.func" "test_func"  
 
##
## construct grid 
##
grid_get -10 10 0.1 -10 10 0.1 
 
##
## create gridding rules
##

# resulting surface at points = points values 
points "7points" 

# resulting surface weighted mean value = value... 
wmean 30 "test_func" 

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
surf_save "wmean.dat" "map_wmean"

set mean_value [surf_wmean test_func map_wmean]
puts "surface weighted mean value is $mean_value"

