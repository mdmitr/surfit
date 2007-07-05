
# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data

# set name of surface
set map_name "kpor_wo_hist"

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-6

##
## load initial data 
##

# load points from text file 
pnts_read "model_prm_2d.txt" "model_prm_2d" 3 4 8 2 "\t" 1

# read areas with undefined values from files
area_read "zones/*.c*"

##
## construct grid 
##
grid_get 58710.507812 73460.507812 50 28760.009766 57210.009766 50

##
## create gridding rules
##

# resulting surface in area = value... 
area undef *

# resulting surface at points = points values 
points "model_prm_2d"

# resulting surface should tend to be constant or plane 
completer 1 20

##
## run gridding algorithm
##
surfit

##
## save results 
##

# save surface to surfit datafile 
surf_save "kpor_wo_hist.dat" $map_name

# plot resulting surface in PostScript
surf_plot "kpor_wo_hist.ps" $map_name