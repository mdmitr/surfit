#
load libfreeflow[info sharedlibextension]

clear_data

surf_load points.dat map_points
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_points

surf_load ppoints.dat map_ppoints
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_ppoints

surf_load parea.dat map_parea
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_parea

surf_load pcurve.dat map_pcurve
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_pcurve

surf_load pcntr.dat map_pcntr
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_pcntr

surf_load ppoints2.dat map_ppoints2
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del map_ppoints2