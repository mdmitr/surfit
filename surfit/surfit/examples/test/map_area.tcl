#
load libsurfit[info sharedlibextension]

# resulting surface must have name "map_area"
set map_name map_area

# reading areas bounds from 2-column text files
areas_read area1.txt area1 10
areas_read area2.txt area2 20
areas_read area3.txt area3 30
areas_read area4.txt area4 40
areas_read area5.txt area5

# setting surface behaviour between areas
completer_set 1 1.6

# constructing grid
grid_get -12 12 0.2 -12 12 0.2

# running CMOFS algorithm
solve

# unloading surfit_grid from memory
grid_unload

# saving results to binary ROFF file
file_save map_area.dat
