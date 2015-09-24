# 
# load plugins
# 
load libfreeflow[info sharedlibextension]

# remove all previous data and functionals
clear_data

# set name of surface
set map_name "map_flow_area"

# set tolerance for cg solver
set tol 5e-7

##
## load initial data 
##

# load curve from text file 
curv_read "press.xyz" "press"

# load area from text file 
area_read "flow_area.txt" "flow_area_center"

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

# add flow from/to area
flow_area -0.00159 "flow_area_center"

##
## run gridding algorithm
##
surfit

##
## save results 
##

# unload grid from memory
grid_unload

# save all to surfit datafile 
file_save "flow_area.dat"

# calculate debit
puts [concat "Debit : " [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ] ]

# plot resulting surface in PostScript
surf_plot "flow_area.ps" $map_name