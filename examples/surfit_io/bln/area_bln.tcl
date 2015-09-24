# 
# load plugins
# 
load libsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]


# load area from text file 
area_read "area1.txt" "area1"  
 
# load area from text file 
area_read "area2.txt" "area2"  
 
# load area from text file 
area_read "area3.txt" "area3"  
 
# load area from text file 
area_read "area4.txt" "area4"  
 
# load area from text file 
area_read "area5.txt" "area5"  

area_save_bln "areas.bln" "area1"

clear_data

area_load_bln "areas.bln" "area1"

area_save_bln "areas2.bln" "area1"