#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_curve_ineq" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 5e-005 

##
## load initial data 
##
 
# load curve from text file 
curv_read "data/iso1.xy" "iso1"  
 
# load curve from text file 
curv_read "data/iso2.xy" "iso2"  
 
# load curve from text file 
curv_read "data/iso3.xy" "iso3"  
 
# load curve from text file 
curv_read "data/iso4.xy" "iso4"  
 
##
## construct grid 
##
grid 10 10 
 
##
## create gridding rules
##

# resulting surface at curve <= value... 
curve_leq 10 "iso1"  

# resulting surface at curve >= value... 
curve_geq 50 "iso3"  

# resulting surface at curve <= value... 
curve_leq 30 "iso4"  

# resulting surface at curve <= value... 
curve_leq 40 "iso2"  

# resulting surface should tend to be constant or plane 
completer 1 1.6  

##
## run gridding algorithm
##
surfit 

##
## save results 
##

# unload grid from memory
grid_unload 

# save surface to surfit datafile 
surf_save "curve_ineq.dat" "map_curve_ineq" 

# plot resulting surface in PostScript
surf_plot "curve_ineq.ps" $map_name