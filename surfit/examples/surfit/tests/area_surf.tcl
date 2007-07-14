#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_area_surf" 

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
 
##
## construct grid 
##
grid_get -12 12 0.2 -12 12 0.2 
 
##
## create gridding rules
##

# resulting surface in area = surface values... 
area_surf "test_func" "area6"  

# resulting surface should tend to be constant or plane 
completer 

# add "resulting surface in area = surface values..." with weight 
area_surf_add "test_func" 0.07 "area1"  

# add "resulting surface in area = surface values..." with weight 
area_surf_add "test_func" 0.1 "area2"  

# add "resulting surface in area = surface values..." with weight 
area_surf_add "test_func" 0.1 "area3"  

# add "resulting surface in area = surface values..." with weight 
area_surf_add "test_func" 0.05 "area4"  

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "area_surf.dat" "map_area_surf" 

# plot resulting surface in EPS
surf_plot "area_surf.eps" $map_name