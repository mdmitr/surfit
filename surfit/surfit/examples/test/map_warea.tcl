#
load libsurfit[info sharedlibextension]

# resulting surface must have name "map_warea"
set map_name map_warea

# reading wareas bounds from 2-column text files
wareas_read area1.txt warea1 10 0.07
wareas_read area2.txt warea2 20 0.07
wareas_read area3.txt warea3 30 0.07
wareas_read area4.txt warea4 40 0.07

# reading area bound from 2-column text file
areas_read area5.txt area5

# setting surface behaviour between areas
completer_set 1 1.6

# constructing surfit_grid
grid_get -12 12 0.2 -12 12 0.2

# running CMOFS algorithm
solve

# unloading surfit_grid from memory
grid_unload

# saving results to binary ROFF file
file_save map_warea.dat
