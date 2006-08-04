#
# This script was generated with funner v2.1beta (www.gridding.info)

# 
# load plugins
# 
load libsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data 

# set name of surface
set map_name "map_faults" 

# set solver
set_solver "cg" 

# set tolerance for solver
set tol 1e-005 

##
## load initial data 
##
 
# load points from text file 
pnts_read "11points.txt" "11points"  
 
# load curve from text file 
curv_read "flt_line1.txt" "flt_line1"  
 
# load curve from text file 
curv_read "flt_line2.txt" "flt_line2"  
 
# load curve from text file 
curv_read "flt_line3.txt" "flt_line3"  
 
# load curve from text file 
curv_read "flt_line4.txt" "flt_line4"  
 
##
## construct grid 
##
grid_get 1 99 1 -50 50 1 
 
##
## create gridding rules
##

# resulting surface at points = points values 
points "11points" 

# resulting surface should tend to be constant or plane 
completer 0.5 2  

# fault line 
fault "flt_line1"  

# fault line 
fault "flt_line2"  

# fault line 
fault "flt_line3"  

# fault line 
fault "flt_line4"  

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
surf_save "fault.dat" "map_faults" 
