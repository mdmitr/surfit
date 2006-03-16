#
load libsurfit[info sharedlibextension]

# removing all previous data and functionals
clear_data

# setting map name for calculating surfit
set map_name map_iso

# set tolerance for cg solver
set tol 1e-5

##
## loading initial data 
##
# reading isolines from 2-column text files
curv_read iso1.xy iso1
curv_read iso2.xy iso2
curv_read iso3.xy iso3
curv_read iso4.xy iso4

##
## constructing grid
##
grid 10 10

##
## constructing functionals sequence
##
curve 10 iso1
curve  50 iso3
curve  30 iso4
completer 1 1.6
curve_add 40 10 iso2

##
## runing cmofs algorithm
##
cmofs

##
## saving results
##

grid_unload
file_save isoline.dat
