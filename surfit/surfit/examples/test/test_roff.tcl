#
load libsurfit[info sharedlibextension]


#defarea
func_load func.func
func_to_defarea 0 60

#wfunc
func_load func.func
func_to_wfunc 0.3

#trend
func_load func.func
func_to_trend 1 2

#func
func_load func.func

area_read area1.txt area1 10
areas_read area2.txt area2 20
areas_read area3.txt area3 30
areas_read area4.txt area4 40
areas_read area5.txt area5

cntr_read cntr_center.xyz cntr_center
cntrs_read cntr_small_circle.xyz cntr_small
cntrs_read cntr_big_circle.xyz cntr_big

flt_read flt_line1.txt flt1
flts_read flt_line2.txt flt2
flts_read flt_line3.txt flt3
flts_read flt_line4.txt flt4

task_read task.txt task

warea_read area1.txt warea1 10 0.07
wareas_read area2.txt warea2 20 0.07
wareas_read area3.txt warea3 30 0.07
wareas_read area4.txt warea4 40 0.07

wcntr_read cntr_center.xyz cntr_center 1000
wcntrs_read cntr_small_circle.xyz cntr_small 10
wcntrs_read cntr_big_circle.xyz cntr_big 0.5

wiso_read iso1.xy iso1 10 1
wisos_read iso2.xy iso2 30 1
wisos_read iso3.xy iso3 50 1
wisos_read iso4.xy iso4 30 1

task_read task.txt task
task_to_wtask 3
    
iso_read iso1.xy iso1 10
isos_read iso2.xy iso2 30
isos_read iso3.xy iso3 50
isos_read iso4.xy iso4 30

completer_set 1 1.6
grid_get -600 600 10 -600 600 10


file_save test_roff.dat
mem_info
clear_data
file_load test_roff.dat
mem_info
