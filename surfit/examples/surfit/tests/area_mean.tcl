#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_area_mean" 

# set tolerance for cg solver
set tol 1e-006 

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
 
##
## construct grid 
##
grid_get -12 12 0.1 -12 12 0.1 
 
##
## create gridding rules
##

# resulting surface in area = value... 
area 10 "area1"  

# resulting surface in area = value... 
area 30 "area3"  

# resulting surface in area = value... 
area undef "area5"  

# resulting surface mean value in area = value... 
area_mean 40 "area6"  

# resulting surface mean value = value... 
mean 30 

# resulting surface should tend to be constant or plane 
completer 1 1.6  

# add "resulting surface in area = value..." with weight 
area_add 20 0.07 "area2"  

# add "surface resulting in area = value..." with weight 
area_add 40 0.07 "area4"  

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "area_mean.dat" "map_area_mean" 

puts [concat "Surface mean value in area6 : " [surf_area_mean "area6" "map_area_mean"]]
puts [concat "Surface mean value : " [surf_mean "map_area_mean"]]

# plot resulting surface in EPS
surf_plot "area_mean.eps" $map_name
