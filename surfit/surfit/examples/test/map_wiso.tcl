#
load libsurfit[info sharedlibextension]

# resulting surface must have name "map_wiso"
set map_name map_wiso

# reading isolines with weights from 2-column text files
wisos_read iso1.xy iso1 10 1.5
wisos_read iso2.xy iso2 40 0.5
wisos_read iso3.xy iso3 50 1.5
wisos_read iso4.xy iso4 30 0.5

# setting surface behaviour between isolines
completer_set 1 1.6

# constructing surfit_grid
grid_get -600 600 10 -600 600 10

# running CMOFS algorithm
solve

# unloading surfit_grid from memory
grid_unload

# saving results to binary ROFF file
file_save map_wiso.dat
