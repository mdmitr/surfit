#

# loading libsurfit shared library
load libsurfit[info sharedlibextension]

set grd_ext ".grd"
set dat_ext ".dat"

proc interp_points { points_filename 
		     stepX 
		     stepY 
		     {completer_D1 1} 
		     {completer_D2 2} 
		     {tolerance 0} } {

	global grd_ext
	global dat_ext
	global map_name
	global tol

	set map_name $points_filename


	# dropping all data from memory
	clear_data

	# reading points from file
	if { [file exists $points_filename] == 0 } {
		putlog "can't find file $points_filename"
		return 0
	}
	task_read $points_filename $points_filename

	if { [task_size] == 0 } {
		putlog "can't read points from file $points_filename"
		return 0
	}

	if { $tolerance == 0 } {
		set tolerance 1e-6
		putlog $tolerance
	}
	set tol $tolerance

	# making equidistant grid
	grid_auto $stepX $stepY

	# setting behaviour between interpolation points
	completer_set $completer_D1 $completer_D2

	# running CMOFS algorithm
	solve

	func_project

	# unloading surfit_grid from memory
	grid_unload

	# saving results
	func_save_grd $points_filename$grd_ext
	file_save $points_filename$dat_ext
}


proc approx_points { points_filename 
		     stepX 
                     stepY 
		     {weight 1} 
		     {completer_D1 1} 
		     {completer_D2 2} 
                     {tolerance 0} } {

	global grd_ext
	global dat_ext
	global tol
	global map_name

	set map_name $points_filename

	# dropping all data from memory
	clear_data

	# reading points from file
	if { [file exists $points_filename] == 0 } {
		putlog "can't find file $points_filename"
		return 0
	}
	task_read $points_filename $points_filename

	if { $tolerance == 0 } {
		set tolerance 5e-7
		putlog $tolerance
	}
	set tol $tolerance

	task_to_wtask $weight

	if { [wtask_size] == 0 } {
		putlog "can't read points from file $points_filename"
		return 0
	}

	# making equidistant grid
	grid_auto $stepX $stepY

	# setting behaviour between interpolation points
	completer_set $completer_D1 $completer_D2

	# running CMOFS algorithm
	solve

	func_project

	# unloading surfit_grid from memory
	grid_unload

	# saving results
	func_save_grd $points_filename$grd_ext
	file_save $points_filename$dat_ext
}
