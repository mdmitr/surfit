
if { [file exists ../seism/map_aoup.dat] == 0 } {
puts ""
puts "Please run ../seism/map_series.tcl first!"
puts ""
return -1
}


source map_aoup.tcl
source map_htotal.tcl
source map_aobt.tcl
source map_woc.tcl
source calc_defareas.tcl
source map_heff.tcl
source map_heffoil.tcl

