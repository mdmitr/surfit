#
load libsurfit[info sharedlibextension]

# resulting surface must have name "map_func"
set map_name map_func

# loading func from binary ROFF file
func_load func.func

# setting surface behaviour between ordered data points
completer_set 2 1

# constructing surfit_grid
grid_get -10 10 0.2 -10 10 0.4

# running CMOFS algorithm
solve

# unloading surfit_grid from memory
grid_unload

# saving results to binary ROFF file
file_save map_func.dat
