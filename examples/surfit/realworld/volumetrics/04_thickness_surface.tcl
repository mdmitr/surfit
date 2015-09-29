#
# This script was generated with funner for surfit v3.0

# 
# load plugins
# 
load libtclsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-006 

##
## load initial data 
##
 
# load surface from surfit datafile 
surf_load "top_surface.dat" "top_surface"  
 
# load surface from surfit datafile 
surf_load "base_surface.dat" "base_surface"  

#calculating total height
surf_minus "base_surface" "top_surface"

#rename
surf_setName "thickness_surface" "base_surface" 

# save surface to surfit datafile 
surf_save "thickness_surface.dat" "thickness_surface" 
