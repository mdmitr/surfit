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
set map_name "peaks" 

# set solver
set_solver "cg" 

# set tolerance for cg solver
set tol 1e-008

##
## load initial data 
##

# load isolines from Surfer BLN file
file_load "peaks25.bln"

# smooth isolines with interpolation DLG scheme
cntr_smooth * 3

##
## construct grid 
##
grid 5 5

##
## create gridding rules
##

# resulting surface should tend to be constant or plane 
completer 0 1

# add "resulting surface should interpolate contours"
contours_add 1

##
## run gridding algorithm
##
surfit 


##
## save results 
##

# save surface to surfit datafile 
surf_save "peaks.dat" $map_name 

# plot resulting surface in PostScript
surf_plot "peaks.ps"


