#
load libsurfit[info sharedlibextension]

# resulting surface must have name "map_defarea"
set map_name map_defarea

# loading func from binary ROFF file
func_load func.func

# convering func to defarea
func_to_defarea 0 60

# loading func from binary ROFF file
func_load func.func

# constructing surfit_grid
grid_get -10 10 0.2 -10 10 0.4

# running CMOFS algorithm
solve

# unloading surfit_grid from memory
grid_unload

# saving results to binary ROFF file
file_save map_defarea.dat
