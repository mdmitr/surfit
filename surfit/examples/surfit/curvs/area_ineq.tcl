#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and functionals
clear_data 

# set name of surface
set map_name "map_area_ineq" 

# set tolerance for cg solver
set tol 1e-005 

##
## load initial data 
##
 
# load area from text file 
area_read "area1.txt" "area1"  
 
# load area from text file 
area_read "area2.txt" "area2"  
 
# load area from text file 
area_read "area3.txt" "area3"  
 
# load area from text file 
area_read "area4.txt" "area4"  
 
# load area from text file 
area_read "area5.txt" "area5"  
 
# load area from text file 
area_read "area6.txt" "area6"  
 
##
## construct grid 
##
grid_get -12 12 0.2 -12 12 0.2 
 
##
## create gridding rules
##

# surface in area = value... 
area 30 "area3"  

# surface in area <= value... 
area_leq 20 "area6"

# surface in area = value... 
area 10 "area1"  

# surface in area = value... 
area undef "area5"  

# surface should tend to be constant or plane 
completer 1 0  

# add "surface in area = value..." with weight 
area_add 20 0.07 "area2"  

# add "surface in area = value..." with weight 
area_add 40 0.07 "area4"  

##
## run cmofs algorithm
##
cmofs 

##
## save results 
##

# unload grid from memory
grid_unload 

# saves function to ROFF file 
func_save "area_ineq.dat" 

puts [concat "Maximum value in area6 : " [func_area_maxz "area6" "map_area_ineq"]]

