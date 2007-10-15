# 
# load plugins
# 
load libfreeflow[info sharedlibextension]

# remove all previous data and functionals
clear_data

# set name of surface
set map_name "map_flow_points"

# set tolerance for cg solver
set tol 5e-7

##
## load initial data 
##

# load curve from text file 
curv_read "press.xyz" "press"

# load points from text file 
pnts_read "flow_point.txt" "center_flow_point"

##
## construct grid 
##
grid_get  -1000 1000 5 -1000 1000 5

##
## create gridding rules
##

# resulting surface at curve = value... 
curve 250 "press"

# law of conservation of mass
lcm_simple 16.4 1 1e-6 

# add flow from/to points
flow_points "center_flow_point"

##
## run gridding algorithm
##
surfit

# unload grid from memory
grid_unload

# save all to surfit datafile 
file_save "flow_points.dat"

# plot resulting surface in PostScript
surf_plot "flow_points.ps" $map_name