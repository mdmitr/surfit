#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_area_surf_ineq" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load area from text file 
area_read "data/area1.txt" "area1"  
 
# load area from text file 
area_read "data/area2.txt" "area2"  
 
# load area from text file 
area_read "data/area3.txt" "area3"  
 
# load area from text file 
area_read "data/area4.txt" "area4"  
 
# load area from text file 
area_read "data/area6.txt" "area6"  
 
# load surface from surfit datafile 
surf_load "data/func.func" "test_func"  
 
# load area from text file 
area_read "data/area5.txt" "area5"  
 
##
## construct grid 
##
grid_get -12 12 0.2 -12 12 0.2 
 
##
## create gridding rules
##

# resulting surface in area >= surface values... 
area_surf_geq "test_func" "area1"  

# resulting surface in area <= surface values... 
area_surf_leq "test_func" "area2"  

# resulting surface in area >= surface values... 
area_surf_geq "test_func" "area3"  

# resulting surface in area <= surface values... 
area_surf_leq "test_func" "area4"  

# resulting surface in area >= surface values... 
area_surf_geq "test_func" "area5"  

# resulting surface in area <= surface values... 
area_surf_leq "test_func" "area6"  

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
surf_save "area_surf_ineq.dat" "map_area_surf_ineq" 

# plot resulting surface in PostScript
surf_plot "area_surf_ineq.ps" $map_name