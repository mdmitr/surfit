#
load libsurfit[info sharedlibextension]

# resulting surface must have name "map_cntr"
set map_name map_cntr

# reading contours from 3-column text files
cntrs_read cntr_center.xyz cntr_center
cntrs_read cntr_small_circle.xyz cntr_small
cntrs_read cntr_big_circle.xyz cntr_big

# setting surface behaviour between contours
completer_set 2 1

# constructing surfit_grid
grid_get -1000 1000 20 -1000 1000 20

# running CMOFS algorithm
solve

# unloading surfit_grid from memory
grid_unload

# saving results to binary ROFF file
file_save map_cntr.dat
