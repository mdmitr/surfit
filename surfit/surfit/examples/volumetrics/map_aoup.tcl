#
load libsurfit[info sharedlibextension]

clear_data
set map_name map_aoup
set tol 5e-7

if { [file exists ../seism/map_aoup.dat] == 0 } {
puts ""
puts "Please run ../seism/map_series.tcl first!"
puts ""
return -1
}


wisos_read isos/iso_2160.xyz    iso_2160    2160 1
wisos_read isos/iso_2160_2.xyz  iso_2160_2  2160 1
wisos_read isos/iso_2170.xyz    iso_2170    2170 1
wisos_read isos/iso_2180.xyz    iso_2180    2180 1
wisos_read isos/iso_2180_2.xyz  iso_2180_2  2180 1
wisos_read isos/iso_2190_2.xyz  iso_2190_2  2190 1
wisos_read isos/iso_2190_3.xyz  iso_2190_3  2190 1
wisos_read isos/iso_2190_4.xyz  iso_2190_4  2190 1
wisos_read isos/iso_2200_2.xyz  iso_2200_2  2200 1
wisos_read isos/iso_2200_3.xyz  iso_2200_3  2200 1
wisos_read isos/iso_2200_5.xyz  iso_2200_5  2200 1
wisos_read isos/iso_2210_2.xyz  iso_2210_2  2210 1
wisos_read isos/iso_2210_3.xyz  iso_2210_3  2210 1
wisos_read isos/iso_2210_5.xyz  iso_2210_5  2210 1
wisos_read isos/iso_2220_2.xyz  iso_2220_2  2220 10
wisos_read isos/iso_2220_3.xyz  iso_2220_3  2220 10
wisos_read isos/iso_2220_5.xyz  iso_2220_5  2220 10
wisos_read isos/iso_2230_2.xyz  iso_2230_2  2230 10
wisos_read isos/iso_2230_3.xyz  iso_2230_3  2230 10
wisos_read isos/iso_2230_5.xyz  iso_2230_5  2230 10
wisos_read isos/iso_2230_7.xyz  iso_2230_7  2230 10
wisos_read isos/iso_2240.xyz    iso_2240    2240 10
wisos_read isos/iso_2240_3.xyz  iso_2240_3  2240 10
task_read aoup.txt aoup
func_load ../seism/map_aoup.dat
func_to_trend 1 2

grid_get 50000 62000 50 52500 66000 50
completer_set 1 2
solve

grid_unload
trend_unload
file_save map_aoup.dat
