#
load libfreeflow[info sharedlibextension]

clear_data
set tol 5e-7

set map_name map_hor_frac

task_read PZab_2001.txt press2001 5 4 3 5 " \t"
# recalc to MPa
task_mult_real 0.1013

wcntr_read lines/P_2001_236_hor.txt P_2001_236_hor 1
# recalc to MPa
wcntr_mult_real 0.1013

ptask_read Q_2001.txt debits2001 5 4 3 5 " \t"
ptask_mult_real -1

isos_read VNK1.txt VNK1 21.4 2 2 1
isos_read VNK2.txt VNK2 21.4 2 2 1
isos_read VNK3.txt VNK3 21.4 2 2 1

area_read ZAM1.txt ZAM1 0 2 2 1
area_value_undef
area_to_areas
area_read ZAM5.txt ZAM5 0 2 2 1
area_value_undef
area_to_areas

flt_read ZAM2.txt ZAM2 2 2 1

piso_read lines/frac_236_hor.txt frac_236_hor -0.000467413

lcm_simple_set 16.4 0.5 1e-6

grid_get 28300 41400 50 45500 64700 50

trace_grid_line
grid_line_write grd_line.txt " "

flow

grid_unload
file_save map_hor_frac.dat
