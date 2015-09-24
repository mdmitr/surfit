#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libglobe[info sharedlibextension]
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_dem" 

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
grid_get 6.4 6.8 0.0005 0 0.48 0.0005 
 
##
## create gridding rules
##

# resulting surface = DEM values 
dem N00E006.hgt 

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
surf_save "dem.dat" 

# plot resulting surface in PostScript
surf_plot "dem.ps" $map_name