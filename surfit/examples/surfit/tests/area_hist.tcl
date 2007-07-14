#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_area_hist" 

# set tolerance for cg solver
set tol 1e-007

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
area_read "data/area5.txt" "area5"  

# load area from text file 
area_read "data/area6.txt" "area6"  

# load histogram from text file
hist_read "data/eq10.txt" 10 40
hist_write "area_hist_src.txt"
 
##
## construct grid 
##
grid_get -12 12 0.2 -12 12 0.2 
 
##
## create gridding rules
##

# resulting surface in area = value... 
area 10 "area1"  

# resulting surface in area = value... 
area 30 "area3"  

# resulting surface in area = value... 
area undef "area5"  

# resulting surface histogram = histogram
hist "*" 

# resulting surface should tend to be constant or plane 
completer 0 1 

# add "resulting surface in area = value..." with weight 
area_add 20 0.07 "area2"  

# add "resulting surface in area = value..." with weight 
area_add 40 0.07 "area4"  

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "area_hist.dat" "map_area_hist" 

hist_del

hist_from_surf * 10
hist_write "area_hist_result.txt"

# plot resulting surface in EPS
surf_plot "area_hist.eps" $map_name