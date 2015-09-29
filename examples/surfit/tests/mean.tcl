#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libtclsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_mean" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-006

##
## load initial data 
##
 
# load points from text file 
pnts_read "data/7points.txt" "7points"  
 
##
## construct grid 
##
grid_get -10 10 0.1 -10 10 0.1
 
##
## create gridding rules
##

# resulting surface at points = points values 
points "7points" 

# resulting surface mean value = value... 
mean 30 0

# resulting surface should tend to be constant or plane 
completer 

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "mean.dat" "map_mean"

set mean_value [surf_mean map_mean]
puts "surface mean value is $mean_value"
                         
# plot resulting surface in PostScript
surf_plot "mean.ps" $map_name