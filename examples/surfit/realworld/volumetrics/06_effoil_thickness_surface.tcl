#
# This script was generated with funner for surfit v3.0

# 
# load plugins
# 
load libtclsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "effoil_thickness" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-006 

##
## load initial data 
##
 
# load area from text file 
area_read "cntrs/ext_woc.xyz" "ext_woc"  
 
# load area from text file 
area_read "cntrs/int_woc.xyz" "int_woc"  
 
# load surface from surfit datafile 
surf_load "eff_thickness.dat" "eff_thickness"  
 
# load points from text file 
pnts_read "effoil_thickness.txt" "effoil_thickness"  
 
##
## construct grid 
##
grid 25 25 
 
##
## create gridding rules
##

# resulting surface in area = surface values... 
area_surf "eff_thickness" "int_woc"  

# resulting surface in area = value... 
area 0 "ext_woc" 0  

# resulting surface at points = points values 
points "effoil_thickness" 

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
surf_save "effoil_thickness.dat" "effoil_thickness" 
