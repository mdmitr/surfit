#
load libsurfit[info sharedlibextension]

# resulting surface must have name "map_flt"
set map_name map_flt

# reading scattered data points for interpolation from 3-column text files 
task_read 11points.txt 11points

# reading fault lines from 2-column text files
flts_read flt_line1.txt flt1
flts_read flt_line2.txt flt2
flts_read flt_line3.txt flt3
flts_read flt_line4.txt flt4

## fast calculation settings 
set tol 1e-5

## "cool result" calculation settings 
# set tol 1e-6

# setting surface behaviour between scattered data points
completer_set 0.5 2

# constructing surfit_grid
grid_get 1 99 1 -50 50 1

# running CMOFS algorithm
solve

# unloading surfit_grid from memory
grid_unload

# saving results to binary ROFF file
file_save map_flt.dat
