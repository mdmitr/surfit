#
# This script was generated with funner v2.0beta

# 
# load modules
# 
load libsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]
#load libacmlbooster[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set resulting surface name
set map_name "top_D5_wo_trend" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-007

##
## load initial data 
##
 
# load points from text file 
pnts_read "data/wells_D51.txt" "wells_D51" 2 3 4 1 " 	" 0  
 
# load surface from surfit datafile 
#surf_load "top_D4.dat" "top_D4"  
 
# load curves from text files 
curv_read "data/faults/fault*.ctr" 
 
##
## construct grid 
##
grid_get 58710.507812 73460.507812 50 28760.009766 57210.009766 50

 
##
## create gridding rules
##

# resulting surface at points = points values 
points "wells_D51" 

# resulting surface looks like trend surface 
#trend 1 2 "top_D4" 

# fault lines 
fault *  

# resulting surface should tend to be constant or plane 
completer 1 25

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# save surface to Surfer-ASCII grid file 
surf_save_grd "top_D5_wo_trend.grd" $map_name 

# plot resulting surface in PostScript
surf_plot "top_D5_wo_trend.ps" $map_name