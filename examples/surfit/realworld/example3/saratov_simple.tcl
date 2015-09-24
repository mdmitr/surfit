#
# This script was generated with funner v2.2

# 
# load plugins
# 
load libsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "saratov_simple" 

# set solver
set_solver "cg" 

# set tolerance for cg solver
set tol 1e-007

##
## load initial data 
##

# load isolines from Surfer BLN file
cntr_load_shp "isolines.shp" * "Z"

cntr_to_pnts 45 *
pnts_write saratov_points.txt

cntr_del *

# load faults from Surfer BLN file
curv_load_shp "faults.shp"

curv_save_bln "faults.bln"

##
## construct grid 
##
grid 25 25
 
##
## create gridding rules
##

#smooth_contour "iso*"
points

# fault lines
fault "fault*"

# resulting surface should tend to be constant or plane 
completer 1 50

# add "resulting surface should interpolate contours"
#smooth_contour_add 3 "iso*"


##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to surfit datafile 
surf_save "saratov_simple.dat" $map_name 

# plot resulting surface in PostScript
surf_plot "saratov_simple.ps" * 50