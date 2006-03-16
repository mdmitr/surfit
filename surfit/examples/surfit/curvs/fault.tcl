#
load libsurfit[info sharedlibextension]

# removing all previous data and functionals
clear_data

# setting map name for calculating surfit
set map_name map_faults

# set tolerance for cg solver
set tol 1e-5

##
## loading initial data 
##
# reading scattered data points for interpolation from 3-column text files 
pnts_read 11points.txt 11points
# reading fault lines from 2-column text files
curv_read flt_line1.txt flt1
curv_read flt_line2.txt flt2
curv_read flt_line3.txt flt3
curv_read flt_line4.txt flt4

##
## constructing grid
##
grid_get 1 99 1 -50 50 1

##
## constructing functionals sequence
##
points 11points
completer 0.5 2
fault_add flt1
fault_add flt2
fault_add flt2
fault_add flt3

##
## runing cmofs algorithm
##
cmofs

##
## saving results
##

grid_unload
file_save fault.dat
