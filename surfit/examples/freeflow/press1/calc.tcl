#
load libfreeflow[info sharedlibextension]

clear_data

surf_load "points.dat" "map_points"
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del "map_points"

surf_load "flow_points.dat" "map_flow_points"
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del "map_flow_points"

surf_load "flow_area.dat" "map_flow_area"
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del "map_flow_area"

surf_load "flow_curve.dat" "map_flow_curve"
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del "map_flow_curve"

surf_load "flow_cntr.dat" "map_flow_cntr"
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del "map_flow_cntr"

surf_load "flow_points2.dat" "map_flow_points2"
puts [ expr 24*3600*[surf_debit_rect -150 -150 150 150 16.4 1 1e-6 ] ]
surf_del "map_flow_points2"

