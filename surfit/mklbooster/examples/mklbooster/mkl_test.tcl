#
# This script was generated with funner v2.0beta

# 
# load plugins
# 
load libsurfit[info sharedlibextension]
load libmklbooster[info sharedlibextension]

# remove all previous data and functionals
clear_data 

# set name of surface
set map_name "points_exact" 

# set extra small tolerance for solvers
set tol 1e-008 

##
## load initial data 
##
 
# load points from text file 
pnts_read "points.txt" "points"  
 
##
## construct grid 
##
grid 150 150 
 
##
## create gridding rules
##

# resulting surface at points = points values
points "points" 

# resulting surface should tend to be constant or plane 
completer 1 2  


##
##
## TEST
##
##

putlog ""
putlog ""
putlog "** "
putlog "** "
putlog [concat "** Threads : " [get_threads] ]
putlog "** "
putlog "** "

# set solver
set_solver "cg"
## run gridding algorithm
surfit 
## delete resulting surface
surf_del "points_exact"

# set solver
set_solver "cg_mkl"
## run gridding algorithm
surfit
## delete resulting surface
surf_del "points_exact"

if { [get_threads] == 2 } {
	init_threads 1
        
	putlog ""
	putlog ""
	putlog "** "
	putlog "** "
	putlog [concat "** Threads : " [get_threads] ]
	putlog "** "
	putlog "** "

	# set solver
	set_solver "cg"
	## run gridding algorithm
	surfit 
	## delete resulting surface
	surf_del "points_exact"

	# set solver
	set_solver "cg_mkl"
	## run gridding algorithm
	surfit
	## delete resulting surface
	surf_del "points_exact"
}


