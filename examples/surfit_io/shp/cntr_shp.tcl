# 
# load plugins
# 
load libtclsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]

# load contour from text file 
cntr_read "cntr_small_circle.xyz" "cntr_small_circle"  
 
# load contour from text file 
cntr_read "cntr1.xyz" "cntr1"  
 
# load contour from text file 
cntr_read "cntr2.xyz" "cntr2"  
 
# load contour from text file 
cntr_read "cntr_big_circle.xyz" "cntr_big_circle"  
 
# load contour from text file 
cntr_read "cntr_center.xyz" "cntr_center"  

cntr_save_shp "cntrs.shp" "cntr_+"

clear_data

cntr_load_shp "cntrs.shp" "cntr_+"