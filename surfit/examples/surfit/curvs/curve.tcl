#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_curve" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load curve from text file 
curv_read "iso1.xy" "iso1"  
 
# load curve from text file 
curv_read "iso2.xy" "iso2"  
 
# load curve from text file 
curv_read "iso3.xy" "iso3"  
 
# load curve from text file 
curv_read "iso4.xy" "iso4"  
 
##
## construct grid 
##
grid 10 10 
 
##
## create gridding rules
##

# resulting surface at curve = value... 
curve 10 "iso1"  

# resulting surface at curve = value... 
curve 50 "iso3"  

# resulting surface at curve = value... 
curve 30 "iso4"  

# resulting surface should tend to be constant or plane 
completer 1 1.6  

# resulting add "surface at curve = value..." with weight 
curve_add 40 0.5 "iso2"  

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
surf_save "curve.dat" "map_curve"
