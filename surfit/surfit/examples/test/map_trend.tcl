#
load libsurfit[info sharedlibextension]

# resulting surface must have name "map_trend"
set map_name map_trend

# reading scattered data points from 3-column text file
task_read 7points.txt 7points

# reading fault line from 2-column text file
flt_read 1fault.txt 1fault

# reading surfit_func from binary ROFF file
func_load func.func

# converting surfit_func to surfit_trend
func_to_trend 1 2

# setting surface behaviour between scattered data points
completer_set 2 1

# constructing surfit_grid
grid_get -10 10 0.2 -10 10 0.4

# running CMOFS algorithm
solve

# unloading surfit_grid from memory
grid_unload

# saving results to binary ROFF file
file_save map_trend.dat
