#
load libfreeflow[info sharedlibextension]

clear_data

set map_name map_task
grid_get  -1000 1000 5 -1000 1000 5
iso_read press.xyz press 250
task_read press_c.xyz press_c
lcm_simple_read lcm_simple.txt law_of_conservation_of_mass

flow
grid_unload
file_save map_task.dat