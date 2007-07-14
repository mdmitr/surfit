#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "top_D4" 

##
## load initial data 
##
 
# load curves from text files 
area_read "data/filter/filter*.ctr" 
 
surf_load_xyz "data/top_D4_strat" "top_D4"
surf_swapxy "top_D4"

surf_filter_in_area "top_D4" "filter*"

##
## save results 
##

# save surface to surfit datafile 
surf_save "top_D4.dat" "top_D4" 

# plot resulting surface in EPS
surf_plot "top_D4.eps" "top_D4"