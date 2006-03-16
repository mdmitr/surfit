#
load libsurfit[info sharedlibextension]

# removing all previous data and functionals
clear_data

# setting map name for calculating surfit
set map_name map_area_wmean

# set tolerance for cg solver
set tol 5e-6

##
## loading initial data 
##
# reading areas bounds from 2-column text files
area_read area1.txt area1
area_read area2.txt area2
area_read area3.txt area3
area_read area4.txt area4
area_read area5.txt area5
area_read area6.txt area6
func_load func.func

##
## constructing grid
##
grid_get -12 12 0.2 -12 12 0.2

##
## constructing functionals sequence
##
area 10 area1
area 30 area3
area undef area5

area_wmean 30 area6 test_func

completer 1 1.6
area_add 20 0.07 area2
area_add 40 0.07 area4

##
## runing cmofs algorithm
##
cmofs

##
## saving results
##
grid_unload
file_save area_wmean.dat

set mean_value [func_area_wmean area6 test_func map_area_wmean]
puts "func weighted mean value for area6 is $mean_value"


