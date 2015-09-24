#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_ineq" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load points from text file 
pnts_read "data/7points.txt" "7points"  
 
##
## construct grid 
##
grid 
 
##
## create gridding rules
##

# resulting surface <= value... 
leq 120  

# resulting surface >= value... 
geq 80  

# resulting surface at points = points values 
points "7points" 

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
surf_save "ineq.dat" "map_ineq"

# plot resulting surface in PostScript
surf_plot "ineq.ps" $map_name