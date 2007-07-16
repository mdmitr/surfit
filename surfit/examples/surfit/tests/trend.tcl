#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_trend" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load points from text file 
pnts_read "data/7points.txt" "7points"  
 
# load curve from text file 
curv_read "data/1fault2.txt" "1fault2"  
 
# load curve from text file 
curv_read "data/1fault.txt" "1fault"  
 
# load surface from surfit datafile 
surf_load "data/func.func" "test_func"  
 
##
## construct grid 
##
grid_get -10 10 0.2 -10 10 0.2 
 
##
## create gridding rules
##

# resulting surface at points = points values 
points "7points" 

# fault line 
fault "1fault"  

# fault line 
fault "1fault2"  

# resulting surface looks like trend surface 
trend 1 10 "test_func" 

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "trend.dat" "map_trend"

# plot resulting surface in PostScript
surf_plot "trend.ps" $map_name