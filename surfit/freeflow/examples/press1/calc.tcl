#
load libfreeflow[info sharedlibextension]

clear_data

lcm_simple_read lcm_simple.txt law_of_conservation_of_mass

func_load map_task.dat map_task
puts [ expr 24*3600*[func_debit_rect -150 -150 150 150] ]

func_load map_ptask.dat map_ptask
puts [ expr 24*3600*[func_debit_rect -150 -150 150 150] ]

func_load map_parea.dat map_parea
puts [ expr 24*3600*[func_debit_rect -150 -150 150 150] ]

func_load map_piso.dat map_piso
puts [ expr 24*3600*[func_debit_rect -150 -150 150 150] ]

func_load map_pcntr.dat map_pcntr
puts [ expr 24*3600*[func_debit_rect -150 -150 150 150] ]

func_load map_wtask_ptask.dat map_wtask_ptask
puts [ expr 24*3600*[func_debit_rect -150 -150 150 150] ]