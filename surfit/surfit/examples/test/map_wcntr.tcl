#
load libsurfit[info sharedlibextension]

# resulting surface must have name "map_wcntr"
set map_name map_wcntr

# reading contours with weights from 3-column text files
wcntrs_read cntr_center.xyz cntr_center 1000
wcntrs_read cntr_small_circle.xyz cntr_small 10
wcntrs_read cntr_big_circle.xyz cntr_big 0.5

# setting surface behaviour between contours
completer_set 2 1

# constructing surfit_grid
grid_get -1000 1000 20 -1000 1000 20

# running CMOFS algorithm
solve

# unloading surfit_grid
grid_unload

# saving results to binary ROFF file
file_save map_wcntr.dat
