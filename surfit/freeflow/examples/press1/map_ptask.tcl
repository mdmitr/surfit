#
load libfreeflow[info sharedlibextension]

clear_data

set map_name map_ptask
grid_get  -1000 1000 5 -1000 1000 5
iso_read press.xyz press 250
ptask_read debit_c.txt debit_c
lcm_simple_read lcm_simple.txt law_of_conservation_of_mass

flow
grid_unload
file_save map_ptask.dat