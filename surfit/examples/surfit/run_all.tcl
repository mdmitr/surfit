load libsurfit[info sharedlibextension]

#
# curvs 
#
cd "curvs"
if { [source "area.tcl"] == 0 } {
	return 0
}
if { [source "area_ineq.tcl"] == 0 } {
	return 0
}
if { [source "area_mean.tcl"] == 0 } {
	return 0
}
if { [source "area_surf.tcl"] == 0 } {
	return 0
}
if { [source "area_surf_ineq.tcl"] == 0 } {
	return 0
}
if { [source "area_wmean.tcl"] == 0 } {
	return 0
}
if { [source "contour.tcl"] == 0 } {
	return 0
}
if { [source "contour_ineq.tcl"] == 0 } {
	return 0
}
if { [source "curve.tcl"] == 0 } {
	return 0
}
if { [source "curve_ineq.tcl"] == 0 } {
	return 0
}
if { [source "curve_surf.tcl"] == 0 } {
	return 0
}
if { [source "curve_surf_ineq.tcl"] == 0 } {
	return 0
}
if { [source "fault.tcl"] == 0 } {
	return 0
}
if { [source "fault_approx.tcl"] == 0 } {
	return 0
}
cd ..

#
# surfaces
#
cd "surfs"
if { [source "mask.tcl"] == 0 } {
	return 0
}
if { [source "surface.tcl"] == 0 } {
	return 0
}
if { [source "surface_add.tcl"] == 0 } {
	return 0
}
if { [source "surface_ineq.tcl"] == 0 } {
	return 0
}
if { [source "trend.tcl"] == 0 } {
	return 0
}
cd ..

#
# others
#
cd "others"
if { [source "ineq.tcl"] == 0 } {
	return 0
}
if { [source "mean.tcl"] == 0 } {
	return 0
}
if { [source "wmean.tcl"] == 0 } {
	return 0
}
cd ..

#
# points
#
cd "points"
if { [source "points_approx.tcl"] == 0 } {
	return 0
}
if { [source "points_exact.tcl"] == 0 } {
	return 0
}
if { [source "points_ineq.tcl"] == 0 } {
	return 0
}
cd ..



