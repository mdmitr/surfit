#
load libfreeflow[info sharedlibextension]

clear_data

surf_load map_task.dat map_task
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_task

surf_load map_ptask.dat map_ptask
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_ptask

surf_load map_parea.dat map_parea
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_parea

surf_load map_piso.dat map_piso
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_piso

surf_load map_pcntr.dat map_pcntr
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_pcntr

surf_load map_wtask_ptask.dat map_wtask_ptask
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_wtask_ptask