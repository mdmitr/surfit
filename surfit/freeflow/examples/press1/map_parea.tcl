#
load libfreeflow[info sharedlibextension]

set tol 5e-7
clear_data

set map_name map_parea
grid_get  -1000 1000 5 -1000 1000 5
iso_read press.xyz press 250
parea_read parea.txt parea_center -0.00159
lcm_simple_read lcm_simple.txt law_of_conservation_of_mass

flow
grid_unload
file_save map_parea.dat