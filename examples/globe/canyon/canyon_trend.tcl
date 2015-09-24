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
set map_name "canyon_trend" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load surface from surfit datafile 
surf_load "N35W112.dat" "N35W112"  
 
# load surface from surfit datafile 
surf_load "N35W113.dat" "N35W113"  
 
# load surface from surfit datafile 
surf_load "N35W114.dat" "N35W114"  
 
# load surface from surfit datafile 
surf_load "N36W112.dat" "N36W112"  
 
# load surface from surfit datafile 
surf_load "N36W113.dat" "N36W113"  
 
# load surface from surfit datafile 
surf_load "N36W114.dat" "N36W114"  
 
# load surface from surfit datafile 
surf_load "N37W112.dat" "N37W112"  
 
# load surface from surfit datafile 
surf_load "N37W113.dat" "N37W113"  
 
# load surface from surfit datafile 
surf_load "N37W114.dat" "N37W114"  
 
##
## construct grid 
##
grid_get -114 -111.6 0.0006 35.6 37 0.0007 
 
##
## create gridding rules
##

# resulting surface = surface values 
surface "N35W112" 

# resulting surface = surface values 
surface "N35W113" 

# resulting surface = surface values 
surface "N35W114" 

# resulting surface = surface values 
surface "N36W112" 

# resulting surface = surface values 
surface "N36W113" 

# resulting surface = surface values 
surface "N36W114" 

# resulting surface = surface values 
surface "N37W112" 

# resulting surface = surface values 
surface "N37W113" 

# resulting surface = surface values 
surface "N37W114" 

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
surf_save "canyon_trend.dat" "canyon_trend" 
