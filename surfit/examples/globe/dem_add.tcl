#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libglobe[info sharedlibextension]
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_dem_add" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# loads DEM from zipped HGT files (Shuttle Radar Topographic Mission files) 
dem_load_hgt_zip "N00E006.hgt.zip" N00E006.hgt  
 
##
## construct grid 
##
grid 0.0005 0.0005 
 
##
## create gridding rules
##

# resulting surface should tend to be constant or plane 
completer 

# add "resulting surface = DEM values" with weight 
dem_add 1 N00E006.hgt 

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
surf_save "dem_add.dat" 
