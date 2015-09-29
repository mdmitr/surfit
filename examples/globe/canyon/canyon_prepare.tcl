# 
# load plugins
# 
load libglobe[info sharedlibextension]
load libtclsurfit[info sharedlibextension]

# remove all previous data and gridding rules
clear_data

#
# convert USA dtm to points inside canyon region
#
dem_load_dtm "usa.hdr" "usa" "usa.bin"
dem_to_pnts "usa"
pnts_setName "canyon_pnts" "usa"
area_read "canyon_rect.txt" "canyon_rect"
pnts_filter_out_area "canyon_pnts" "canyon_rect"
pnts_save "canyon_pnts.dat" "canyon_pnts"
clear_data

#
# convert N35W112 DEM to surface and save it to surfit datafile
#
dem_load_hgt_zip "N35W112.hgt.zip" "N35W112.hgt" 
dem_to_surf "N35W112.hgt"
surf_setName "N35W112" "N35W112.hgt"
surf_save "N35W112.dat" "N35W112"
clear_data

#
# convert N35W113 DEM to surface and save it to surfit datafile
#
dem_load_hgt_zip "N35W113.hgt.zip" "N35W113.hgt" 
dem_to_surf "N35W113.hgt"
surf_setName "N35W113" "N35W113.hgt"
surf_save "N35W113.dat" "N35W113"
clear_data

#
# convert N35W114 DEM to surface and save it to surfit datafile
#
dem_load_hgt_zip "N35W114.hgt.zip" "N35W114.hgt" 
dem_to_surf "N35W114.hgt"
surf_setName "N35W114" "N35W114.hgt"
surf_save "N35W114.dat" "N35W114"
clear_data

#
# convert N36W112 DEM to surface and save it to surfit datafile
#
dem_load_hgt_zip "N36W112.hgt.zip" "N36W112.hgt" 
dem_to_surf "N36W112.hgt"
surf_setName "N36W112" "N36W112.hgt"
surf_save "N36W112.dat" "N36W112"
clear_data

#
# convert N36W113 DEM to surface and save it to surfit datafile
#
dem_load_hgt_zip "N36W113.hgt.zip" "N36W113.hgt" 
dem_to_surf "N36W113.hgt"
surf_setName "N36W113" "N36W113.hgt"
surf_save "N36W113.dat" "N36W113"
clear_data

#
# convert N36W114 DEM to surface and save it to surfit datafile
#
dem_load_hgt_zip "N36W114.hgt.zip" "N36W114.hgt" 
dem_to_surf "N36W114.hgt"
surf_setName "N36W114" "N36W114.hgt"
surf_save "N36W114.dat" "N36W114"
clear_data

#
# convert N37W112 DEM to surface and save it to surfit datafile
#
dem_load_hgt_zip "N37W112.hgt.zip" "N37W112.hgt" 
dem_to_surf "N37W112.hgt"
surf_setName "N37W112" "N37W112.hgt"
surf_save "N37W112.dat" "N37W112"
clear_data

#
# convert N37W113 DEM to surface and save it to surfit datafile
#
dem_load_hgt_zip "N37W113.hgt.zip" "N37W113.hgt" 
dem_to_surf "N37W113.hgt"
surf_setName "N37W113" "N37W113.hgt"
surf_save "N37W113.dat" "N37W113"
clear_data

#
# convert N37W114 DEM to surface and save it to surfit datafile
#
dem_load_hgt_zip "N37W114.hgt.zip" "N37W114.hgt" 
dem_to_surf "N37W114.hgt"
surf_setName "N37W114" "N37W114.hgt"
surf_save "N37W114.dat" "N37W114"
clear_data



