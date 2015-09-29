# 
# load plugins
# 
load libtclsurfit[info sharedlibextension]
load libsurfit_io[info sharedlibextension]


##
## load initial data 
##
 
# load curve from text file 
curv_read "iso1.xy" "iso1"  
 
# load curve from text file 
curv_read "iso2.xy" "iso2"  
 
# load curve from text file 
curv_read "iso3.xy" "iso3"  
 
# load curve from text file 
curv_read "iso4.xy" "iso4"  

                               
curv_save_bln "curvs.bln" "iso*"

clear_data

curv_load_bln "curvs.bln" "iso\[1-3\]"