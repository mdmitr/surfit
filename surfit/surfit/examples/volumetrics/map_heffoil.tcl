#
load libsurfit[info sharedlibextension]

if { [file exists oil.dat] == 0 } {
puts ""
puts "Please run calc_defareas.tcl first!"
puts ""
return -1
}

if { [file exists water_and_oil.dat] == 0 } {
puts ""
puts "Please run calc_defareas.tcl first!"
puts ""
return -1
}

if { [file exists map_heff.dat] == 0 } {
puts ""
puts "Please run map_heff.tcl first!"
puts ""
return -1
}


clear_data
set tol 5e-5


# calculation of "water" zone
set map_name water_zone
grid_get 54000 60000 25 55000 62000 25
defarea_load water_and_oil.dat
defarea_not
fill_with_set 0
completer_set 1 3

solve

fill_with_unload
defarea_unload
func_save water_zone.dat



# calculation of "oil" zone
set map_name oil_zone
clear_data
grid_get 54000 60000 25 55000 62000 25
defarea_load oil.dat oil
func_load map_heff.dat map_heff
func_to_wfunc 10000
completer_set 1 1.3

solve

func_save oil_zone.dat oil_zone

# calculation of "oil" and "oil+water" zones
set map_name map_heffoil
clear_data
grid_get 54000 60000 25 55000 62000 25
funcs_load oil_zone.dat oil_zone
funcs_load water_zone.dat water_zone
task_read heffoil.txt
completer_set 1 3

solve

grid_unload
funcs_delall
file_save map_heffoil.dat

