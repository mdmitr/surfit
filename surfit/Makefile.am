AUTOMAKE_OPTIONS = foreign

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

INCLUDES = $(TCLINCLUDE) $(NETCDFINCLUDE) -Isrc/sstuff -Isrc/sstuff/ptypes -Isrc/surfit -Isrc/freeflow -Isrc/surfit_io
EXTRA_DIST = vc6/surfit*
EXTRA_DIST += vc6/freeflow*
EXTRA_DIST += vc6/globe*
EXTRA_DIST += src/surfit/interface/*.i
EXTRA_DIST += examples/*
EXTRA_DIST += src/freeflow/interface/*.i
EXTRA_DIST += src/globe/interface/*.i
EXTRA_DIST += src/surfit_io/interface/*.i
EXTRA_DIST += doc/gallery/*
EXTRA_DIST += doc/src/*
EXTRA_DIST += doc/html/*
EXTRA_DIST += doc/surfit.cfg
EXTRA_DIST += doc/make_doc*
EXTRA_DIST += make_release.bat
EXTRA_DIST += make_debug.bat
EXTRA_DIST += clean.bat
EXTRA_DIST += make_rpm_fc4
EXTRA_DIST += make_rpm_rh73
EXTRA_DIST += surfit.spec.fc4
EXTRA_DIST += surfit.spec.rh73
EXTRA_DIST += CHANGES

lib_LTLIBRARIES = libsstuff.la 
lib_LTLIBRARIES += libsurfit.la 

if MAKE_FREEFLOW
lib_LTLIBRARIES += libfreeflow.la 
endif

if MAKE_GLOBE
lib_LTLIBRARIES += libglobe.la 
endif

if MAKE_SURFIT_IO
lib_LTLIBRARIES += libsurfit_io.la
endif

libsstuff_ladir = $(prefix)/include/sstuff
libsstuff_la_SOURCES =  src/sstuff/bitvec.cpp       
libsstuff_la_SOURCES += src/sstuff/boolvec.cpp      
libsstuff_la_SOURCES += src/sstuff/datafile.cpp     
libsstuff_la_SOURCES += src/sstuff/fileio.cpp       
libsstuff_la_SOURCES += src/sstuff/geom_alg.cpp     
libsstuff_la_SOURCES += src/sstuff/interp.cpp       
libsstuff_la_SOURCES += src/sstuff/intvec.cpp       
libsstuff_la_SOURCES += src/sstuff/read_txt.cpp     
libsstuff_la_SOURCES += src/sstuff/rnd.cpp          
libsstuff_la_SOURCES += src/sstuff/shortvec.cpp     
libsstuff_la_SOURCES += src/sstuff/strvec.cpp
libsstuff_la_SOURCES += src/sstuff/sstuff.cpp       
libsstuff_la_SOURCES += src/sstuff/stepFunc.cpp     
libsstuff_la_SOURCES += src/sstuff/vec.cpp          
libsstuff_la_SOURCES += src/sstuff/vec_alg.cpp      
libsstuff_la_SOURCES += src/sstuff/threads.cpp      
if HAVE_PTHREAD_INSTALLED
libsstuff_la_SOURCES += src/sstuff/ptypes/pasync.cxx
libsstuff_la_SOURCES += src/sstuff/ptypes/patomic.cxx
libsstuff_la_SOURCES += src/sstuff/ptypes/pexcept.cxx
libsstuff_la_SOURCES += src/sstuff/ptypes/pfatal.cxx
libsstuff_la_SOURCES += src/sstuff/ptypes/pmem.cxx
libsstuff_la_SOURCES += src/sstuff/ptypes/pmsgq.cxx
libsstuff_la_SOURCES += src/sstuff/ptypes/psemaphore.cxx
libsstuff_la_SOURCES += src/sstuff/ptypes/pstring.cxx
libsstuff_la_SOURCES += src/sstuff/ptypes/pthread.cxx
libsstuff_la_SOURCES += src/sstuff/ptypes/ptimedsem.cxx
libsstuff_la_SOURCES += src/sstuff/ptypes/punknown.cxx
endif


libsstuff_la_HEADERS =  src/sstuff/bitvec.h       
libsstuff_la_HEADERS += src/sstuff/bitvec_alg.h   
libsstuff_la_HEADERS += src/sstuff/boolvec.h      
libsstuff_la_HEADERS += src/sstuff/byteswap_alg.h 
libsstuff_la_HEADERS += src/sstuff/config.h       
libsstuff_la_HEADERS += src/sstuff/datafile.h     
libsstuff_la_HEADERS += src/sstuff/fileio.h       
libsstuff_la_HEADERS += src/sstuff/geom_alg.h     
libsstuff_la_HEADERS += src/sstuff/interp.h       
libsstuff_la_HEADERS += src/sstuff/intvec.h       
libsstuff_la_HEADERS += src/sstuff/read_txt.h     
libsstuff_la_HEADERS += src/sstuff/real.h         
libsstuff_la_HEADERS += src/sstuff/rnd.h          
libsstuff_la_HEADERS += src/sstuff/shortvec.h     
libsstuff_la_HEADERS += src/sstuff/strvec.h
libsstuff_la_HEADERS += src/sstuff/sstuff.h       
libsstuff_la_SOURCES += src/sstuff/sstuff_ie.h    
libsstuff_la_HEADERS += src/sstuff/stepFunc.h     
libsstuff_la_HEADERS += src/sstuff/vec.h          
libsstuff_la_HEADERS += src/sstuff/vec_alg.h      
libsstuff_la_HEADERS += src/sstuff/threads.h      
if HAVE_PTHREAD_INSTALLED
libsstuff_la_HEADERS += src/sstuff/ptypes/pasync.h
libsstuff_la_HEADERS += src/sstuff/ptypes/pport.h
libsstuff_la_HEADERS += src/sstuff/ptypes/ptypes.h
endif


libsstuff_la_LIBADD = $(LIBS_SURFIT) $(TCLLIB)
libsstuff_la_LDFLAGS = -version-info 2:1:0 -no-undefined --dllname libsstuff.dll

if HAVE_PTHREAD_INSTALLED
libsstuff_la_LIBADD += -lpthread 
endif



libsurfit_ladir = $(prefix)/include/surfit
libsurfit_la_SOURCES =  src/surfit/area.cpp                                                      
libsurfit_la_SOURCES += src/surfit/area_internal.cpp                                             
libsurfit_la_SOURCES += src/surfit/area_tcl.cpp                                                  
libsurfit_la_SOURCES += src/surfit/cmofs.cpp                                                     
libsurfit_la_SOURCES += src/surfit/cntr.cpp                                                      
libsurfit_la_SOURCES += src/surfit/cntr_internal.cpp                                             
libsurfit_la_SOURCES += src/surfit/cntr_tcl.cpp                                                  
libsurfit_la_SOURCES += src/surfit/curv.cpp                                                      
libsurfit_la_SOURCES += src/surfit/curvs_tcl.cpp                                                  
libsurfit_la_SOURCES += src/surfit/curv_internal.cpp                                             
libsurfit_la_SOURCES += src/surfit/curv_tcl.cpp                                                  
libsurfit_la_SOURCES += src/surfit/data.cpp                                                      
libsurfit_la_SOURCES += src/surfit/data_manager.cpp                                              
libsurfit_la_SOURCES += src/surfit/free_elements.cpp                                                    
libsurfit_la_SOURCES += src/surfit/functional.cpp                                                
libsurfit_la_SOURCES += src/surfit/f_area.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_area_surf.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_area_surf_ineq.cpp                                          
libsurfit_la_SOURCES += src/surfit/f_area_ineq.cpp                                               
libsurfit_la_SOURCES += src/surfit/f_area_mean.cpp                                               
libsurfit_la_SOURCES += src/surfit/f_area_wmean.cpp                                              
libsurfit_la_SOURCES += src/surfit/f_cntr.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_cntr_ineq.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_completer.cpp                                               
libsurfit_la_SOURCES += src/surfit/f_curv.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_curv_ineq.cpp 
libsurfit_la_SOURCES += src/surfit/f_curv_surf.cpp
libsurfit_la_SOURCES += src/surfit/f_curv_surf_ineq.cpp
libsurfit_la_SOURCES += src/surfit/f_surf.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_surf_ineq.cpp                                               
libsurfit_la_SOURCES += src/surfit/f_hist.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_ineq.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_mask.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_mask_ineq.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_mask_surf.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_mask_surf_ineq.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_mask_mean.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_mask_wmean.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_mean.cpp                                                    
libsurfit_la_SOURCES += src/surfit/f_points.cpp                                                  
libsurfit_la_SOURCES += src/surfit/f_points_ineq.cpp                                             
libsurfit_la_SOURCES += src/surfit/f_points_tcl.cpp                                              
libsurfit_la_SOURCES += src/surfit/f_trend.cpp                                                   
libsurfit_la_SOURCES += src/surfit/f_value.cpp                                                   
libsurfit_la_SOURCES += src/surfit/f_wmean.cpp                                                   
libsurfit_la_SOURCES += src/surfit/grid.cpp                                                      
libsurfit_la_SOURCES += src/surfit/grid_internal.cpp                                             
libsurfit_la_SOURCES += src/surfit/grid_line.cpp                                                 
libsurfit_la_SOURCES += src/surfit/grid_line_internal.cpp                                        
libsurfit_la_SOURCES += src/surfit/grid_line_tcl.cpp                                              
libsurfit_la_SOURCES += src/surfit/grid_line_user.cpp                                            
libsurfit_la_SOURCES += src/surfit/grid_tcl.cpp                                                  
libsurfit_la_SOURCES += src/surfit/grid_user.cpp                                                 
libsurfit_la_SOURCES += src/surfit/hist.cpp                                                      
libsurfit_la_SOURCES += src/surfit/hist_internal.cpp                                             
libsurfit_la_SOURCES += src/surfit/hist_tcl.cpp                                                  
libsurfit_la_SOURCES += src/surfit/license.cpp                                                   
libsurfit_la_SOURCES += src/surfit/mask.cpp                                                      
libsurfit_la_SOURCES += src/surfit/mask_internal.cpp                                             
libsurfit_la_SOURCES += src/surfit/mask_tcl.cpp                                                  
libsurfit_la_SOURCES += src/surfit/matlab.cpp                                                    
libsurfit_la_SOURCES += src/surfit/matr.cpp                                                      
libsurfit_la_SOURCES += src/surfit/matrD1.cpp                                                    
libsurfit_la_SOURCES += src/surfit/matrD1_aniso.cpp                                                    
libsurfit_la_SOURCES += src/surfit/matrD1_rect.cpp                                               
libsurfit_la_SOURCES += src/surfit/matrD2.cpp                                                    
#libsurfit_la_SOURCES += src/surfit/matrD2_aniso.cpp
libsurfit_la_SOURCES += src/surfit/matrD2_rect.cpp                                               
libsurfit_la_SOURCES += src/surfit/matr_diag.cpp                                                 
libsurfit_la_SOURCES += src/surfit/matr_eye.cpp                                                  
libsurfit_la_SOURCES += src/surfit/matr_onesrow.cpp                                              
libsurfit_la_SOURCES += src/surfit/mrf.cpp                                                        
libsurfit_la_SOURCES += src/surfit/others_tcl.cpp
libsurfit_la_SOURCES += src/surfit/pnts_internal.cpp                                             
libsurfit_la_SOURCES += src/surfit/pnts_tcl.cpp                                                  
libsurfit_la_SOURCES += src/surfit/points.cpp                                                    
libsurfit_la_SOURCES += src/surfit/solvers.cpp                                                   
libsurfit_la_SOURCES += src/surfit/sort_alg.cpp          
libsurfit_la_SOURCES += src/surfit/surf.cpp                                                      
libsurfit_la_SOURCES += src/surfit/surfs_tcl.cpp                                                 
libsurfit_la_SOURCES += src/surfit/surf_internal.cpp                                             
libsurfit_la_SOURCES += src/surfit/surf_tcl.cpp                                                  
libsurfit_la_SOURCES += src/surfit/surfit.cpp            
libsurfit_la_SOURCES += src/surfit/surfit_wrap.cxx       
libsurfit_la_SOURCES += src/surfit/variables.cpp         
libsurfit_la_SOURCES += src/surfit/solvers/CG.cpp
libsurfit_la_SOURCES += src/surfit/solvers/J.cpp
libsurfit_la_SOURCES += src/surfit/solvers/JCG.cpp
libsurfit_la_SOURCES += src/surfit/solvers/RF.cpp
libsurfit_la_SOURCES += src/surfit/solvers/SSOR.cpp


libsurfit_la_HEADERS  = src/surfit/area.h              
libsurfit_la_HEADERS += src/surfit/area_internal.h     
libsurfit_la_SOURCES += src/surfit/area_tcl.h          
libsurfit_la_HEADERS += src/surfit/cmofs.h             
libsurfit_la_HEADERS += src/surfit/cntr.h              
libsurfit_la_HEADERS += src/surfit/cntr_internal.h     
libsurfit_la_SOURCES += src/surfit/cntr_tcl.h          
libsurfit_la_HEADERS += src/surfit/curv.h              
libsurfit_la_SOURCES += src/surfit/curvs_tcl.h         
libsurfit_la_HEADERS += src/surfit/curv_internal.h     
libsurfit_la_SOURCES += src/surfit/curv_tcl.h          
libsurfit_la_HEADERS += src/surfit/surfit_data.h              
libsurfit_la_HEADERS += src/surfit/data_manager.h      
libsurfit_la_HEADERS += src/surfit/free_elements.h     
libsurfit_la_HEADERS += src/surfit/functional.h        
libsurfit_la_HEADERS += src/surfit/f_area.h            
libsurfit_la_HEADERS += src/surfit/f_area_surf.h            
libsurfit_la_HEADERS += src/surfit/f_area_surf_ineq.h  
libsurfit_la_HEADERS += src/surfit/f_area_ineq.h       
libsurfit_la_HEADERS += src/surfit/f_area_mean.h       
libsurfit_la_HEADERS += src/surfit/f_area_wmean.h      
libsurfit_la_HEADERS += src/surfit/f_cntr.h      
libsurfit_la_HEADERS += src/surfit/f_cntr_ineq.h 
libsurfit_la_HEADERS += src/surfit/f_curv.h                 
libsurfit_la_HEADERS += src/surfit/f_curv_ineq.h                 
libsurfit_la_HEADERS += src/surfit/f_completer.h       
libsurfit_la_HEADERS += src/surfit/f_curv_surf.h
libsurfit_la_HEADERS += src/surfit/f_curv_surf_ineq.h
libsurfit_la_HEADERS += src/surfit/f_surf.h            
libsurfit_la_HEADERS += src/surfit/f_surf_ineq.h       
libsurfit_la_HEADERS += src/surfit/f_hist.h            
libsurfit_la_HEADERS += src/surfit/f_ineq.h            
libsurfit_la_HEADERS += src/surfit/f_mask.h            
libsurfit_la_HEADERS += src/surfit/f_mask_ineq.h            
libsurfit_la_HEADERS += src/surfit/f_mask_surf.h            
libsurfit_la_HEADERS += src/surfit/f_mask_surf_ineq.h            
libsurfit_la_HEADERS += src/surfit/f_mask_mean.h            
libsurfit_la_HEADERS += src/surfit/f_mask_wmean.h            
libsurfit_la_HEADERS += src/surfit/f_mean.h            
libsurfit_la_HEADERS += src/surfit/f_points.h          
libsurfit_la_HEADERS += src/surfit/f_points_ineq.h     
libsurfit_la_SOURCES += src/surfit/f_points_tcl.h      
libsurfit_la_HEADERS += src/surfit/f_trend.h           
libsurfit_la_HEADERS += src/surfit/f_value.h           
libsurfit_la_HEADERS += src/surfit/f_wmean.h           
libsurfit_la_HEADERS += src/surfit/grid.h              
libsurfit_la_HEADERS += src/surfit/grid_internal.h     
libsurfit_la_HEADERS += src/surfit/grid_line.h         
libsurfit_la_HEADERS += src/surfit/grid_line_internal.h
libsurfit_la_SOURCES += src/surfit/grid_line_tcl.h     
libsurfit_la_HEADERS += src/surfit/grid_line_user.h    
libsurfit_la_SOURCES += src/surfit/grid_tcl.h          
libsurfit_la_HEADERS += src/surfit/grid_user.h         
libsurfit_la_HEADERS += src/surfit/hist.h              
libsurfit_la_HEADERS += src/surfit/hist_internal.h     
libsurfit_la_SOURCES += src/surfit/hist_tcl.h          
libsurfit_la_HEADERS += src/surfit/license.h           
libsurfit_la_HEADERS += src/surfit/mask.h              
libsurfit_la_HEADERS += src/surfit/mask_internal.h     
libsurfit_la_SOURCES += src/surfit/mask_tcl.h          
libsurfit_la_HEADERS += src/surfit/matfile.h           
libsurfit_la_HEADERS += src/surfit/matlab.h            
libsurfit_la_HEADERS += src/surfit/matr.h              
libsurfit_la_HEADERS += src/surfit/matrD1.h            
libsurfit_la_HEADERS += src/surfit/matrD1_aniso.h            
libsurfit_la_HEADERS += src/surfit/matrD2.h            
#libsurfit_la_HEADERS += src/surfit/matrD2_aniso.h
libsurfit_la_HEADERS += src/surfit/matr_diag.h         
libsurfit_la_HEADERS += src/surfit/matr_eye.h          
libsurfit_la_HEADERS += src/surfit/matr_onesrow.h      
libsurfit_la_HEADERS += src/surfit/mrf.h               
libsurfit_la_SOURCES += src/surfit/other_tcl.h
libsurfit_la_SOURCES += src/surfit/others_tcl.h
libsurfit_la_HEADERS += src/surfit/pnts_internal.h     
libsurfit_la_SOURCES += src/surfit/pnts_tcl.h          
libsurfit_la_HEADERS += src/surfit/points.h            
libsurfit_la_HEADERS += src/surfit/solvers.h           
libsurfit_la_HEADERS += src/surfit/sort_alg.h          
libsurfit_la_HEADERS += src/surfit/surfit.h            
libsurfit_la_HEADERS += src/surfit/solvers.h
libsurfit_la_HEADERS += src/surfit/surf.h              
libsurfit_la_SOURCES += src/surfit/surfs_tcl.h         
libsurfit_la_HEADERS += src/surfit/surf_internal.h     
libsurfit_la_SOURCES += src/surfit/surf_tcl.h          
libsurfit_la_SOURCES += src/surfit/surfit_ie.h                
libsurfit_la_HEADERS += src/surfit/surfit_solvers.h  
libsurfit_la_HEADERS += src/surfit/variables.h         
libsurfit_la_HEADERS += src/surfit/variables_internal.h
libsurfit_la_HEADERS += src/surfit/variables_tcl.h     


libsurfit_la_LIBADD = $(LIBS_SURFIT) $(TCLLIB) libsstuff.la 
libsurfit_la_LDFLAGS = -version-info 2:1:0 -no-undefined --dllname libsurfit.dll


libsurfit_io_ladir = $(prefix)/include/surfit_io


libsurfit_io_la_SOURCES =  src/surfit_io/area_bln.cpp              
libsurfit_io_la_SOURCES += src/surfit_io/area_io_tcl.cpp           
libsurfit_io_la_SOURCES += src/surfit_io/area_shp.cpp              
libsurfit_io_la_SOURCES += src/surfit_io/cntr_io_tcl.cpp           
libsurfit_io_la_SOURCES += src/surfit_io/cntr_shp.cpp              
libsurfit_io_la_SOURCES += src/surfit_io/curv_bln.cpp              
libsurfit_io_la_SOURCES += src/surfit_io/curv_io_tcl.cpp           
libsurfit_io_la_SOURCES += src/surfit_io/curv_shp.cpp              
libsurfit_io_la_SOURCES += src/surfit_io/pnts_io_tcl.cpp           
libsurfit_io_la_SOURCES += src/surfit_io/pnts_shp.cpp              
libsurfit_io_la_SOURCES += src/surfit_io/surfit_io.cpp             
libsurfit_io_la_SOURCES += src/surfit_io/surfit_io_data_manager.cpp
libsurfit_io_la_SOURCES += src/surfit_io/surfit_io_variables.cpp   
libsurfit_io_la_SOURCES += src/surfit_io/surf_arcgis.cpp           
libsurfit_io_la_SOURCES += src/surfit_io/surf_bmp.cpp              
libsurfit_io_la_SOURCES += src/surfit_io/surf_gmt.cpp              
libsurfit_io_la_SOURCES += src/surfit_io/surf_grass.cpp            
libsurfit_io_la_SOURCES += src/surfit_io/surf_grd.cpp              
libsurfit_io_la_SOURCES += src/surfit_io/surf_io_tcl.cpp           
libsurfit_io_la_SOURCES += src/surfit_io/surf_jpg.cpp              
libsurfit_io_la_SOURCES += src/surfit_io/surf_xyz.cpp              
libsurfit_io_la_SOURCES += src/surfit_io/surfit_io_wrap.cxx              
# shapelib
libsurfit_io_la_SOURCES += src/surfit_io/shapelib/shapefil.h
libsurfit_io_la_SOURCES += src/surfit_io/shapelib/dbfopen.c
libsurfit_io_la_SOURCES += src/surfit_io/shapelib/shpopen.c
# EasyBmp
libsurfit_io_la_SOURCES += src/surfit_io/EasyBmp/EasyBMP.cpp
libsurfit_io_la_SOURCES += src/surfit_io/EasyBmp/EasyBMP.h
libsurfit_io_la_SOURCES += src/surfit_io/EasyBmp/EasyBMP_BMP.h
libsurfit_io_la_SOURCES += src/surfit_io/EasyBmp/EasyBMP_DataStructures.h
libsurfit_io_la_SOURCES += src/surfit_io/EasyBmp/EasyBMP_VariousBMPutilities.h


libsurfit_io_la_HEADERS  =  src/surfit_io/area_io.h               
libsurfit_io_la_SOURCES  += src/surfit_io/area_io_tcl.h           
libsurfit_io_la_HEADERS  += src/surfit_io/cntr_io.h               
libsurfit_io_la_SOURCES  += src/surfit_io/cntr_io_tcl.h           
libsurfit_io_la_HEADERS  += src/surfit_io/curv_io.h               
libsurfit_io_la_SOURCES  += src/surfit_io/curv_io_tcl.h           
libsurfit_io_la_HEADERS  += src/surfit_io/pnts_io.h               
libsurfit_io_la_SOURCES  += src/surfit_io/pnts_io_tcl.h           
libsurfit_io_la_HEADERS  += src/surfit_io/surfit_io.h             
libsurfit_io_la_HEADERS  += src/surfit_io/surfit_io_data_manager.h
libsurfit_io_la_SOURCES  += src/surfit_io/surfit_io_ie.h          
libsurfit_io_la_SOURCES  += src/surfit_io/surfit_io_tcl.h         
libsurfit_io_la_HEADERS  += src/surfit_io/surfit_io_variables.h   
libsurfit_io_la_HEADERS  += src/surfit_io/surf_io.h               
libsurfit_io_la_SOURCES  += src/surfit_io/surf_io_tcl.h           


libsurfit_io_la_LIBADD = $(LIBS_SURFIT) $(TCLLIB) $(NETCDFLIB) libsstuff.la libsurfit.la
if HAVE_JPEG_INSTALLED
libsurfit_io_la_LIBADD += -ljpeg
endif
libsurfit_io_la_LDFLAGS = -version-info 2:1:0 -no-undefined --dllname libsurfit_io.dll


libfreeflow_ladir = $(prefix)/include/freeflow
libfreeflow_la_SOURCES  = src/freeflow/flow_data_manager.cpp 
libfreeflow_la_SOURCES += src/freeflow/flow_surf_internal.cpp 
libfreeflow_la_SOURCES += src/freeflow/flow_surf_tcl.cpp 
libfreeflow_la_SOURCES += src/freeflow/flow_variables.cpp    
libfreeflow_la_SOURCES += src/freeflow/freeflow_wrap.cxx     
libfreeflow_la_SOURCES += src/freeflow/f_lcm_simple.cpp      
libfreeflow_la_SOURCES += src/freeflow/f_lcm_simple_tcl.cpp  
libfreeflow_la_SOURCES += src/freeflow/flow_curvs_tcl.cpp        
libfreeflow_la_SOURCES += src/freeflow/flow_area.cpp         
libfreeflow_la_SOURCES += src/freeflow/flow_cntr.cpp         
libfreeflow_la_SOURCES += src/freeflow/flow_curv.cpp          
libfreeflow_la_SOURCES += src/freeflow/flow_points.cpp       
libfreeflow_la_SOURCES += src/freeflow/flow_points_tcl.cpp   

libfreeflow_la_HEADERS  = src/freeflow/flow_data_manager.h     
libfreeflow_la_HEADERS += src/freeflow/flow_surf_internal.h 
libfreeflow_la_SOURCES += src/freeflow/flow_surf_tcl.h 
libfreeflow_la_SOURCES += src/freeflow/flow_ie.h               
libfreeflow_la_HEADERS += src/freeflow/flow_variables.h        
libfreeflow_la_HEADERS += src/freeflow/f_lcm_simple.h          
libfreeflow_la_SOURCES += src/freeflow/f_lcm_simple_tcl.h      
libfreeflow_la_SOURCES += src/freeflow/flow_curvs_tcl.h            
libfreeflow_la_HEADERS += src/freeflow/flow_area.h             
libfreeflow_la_HEADERS += src/freeflow/flow_cntr.h             
libfreeflow_la_HEADERS += src/freeflow/flow_curv.h              
libfreeflow_la_HEADERS += src/freeflow/flow_points.h           
libfreeflow_la_SOURCES += src/freeflow/flow_points_tcl.h       

libfreeflow_la_LIBADD = $(LIBS_SURFIT) $(TCLLIB) libsstuff.la libsurfit.la
libfreeflow_la_LDFLAGS = -version-info 2:1:0 -no-undefined --dllname libfreeflow.dll

libglobe_ladir = $(prefix)/include/globe
libglobe_la_SOURCES  = src/globe/dem.cpp                
libglobe_la_SOURCES += src/globe/dems_tcl.cpp           
libglobe_la_SOURCES += src/globe/dem_internal.cpp       
libglobe_la_SOURCES += src/globe/dem_tcl.cpp            
libglobe_la_SOURCES += src/globe/f_dem.cpp              
libglobe_la_SOURCES += src/globe/globe.cpp              
libglobe_la_SOURCES += src/globe/globe_data_manager.cpp 
libglobe_la_SOURCES += src/globe/globe_surf_internal.cpp
libglobe_la_SOURCES += src/globe/globe_surf_tcl.cpp     
libglobe_la_SOURCES += src/globe/globe_variables.cpp    
libglobe_la_SOURCES += src/globe/globe_wrap.cxx         
libglobe_la_SOURCES += src/globe/shortmrf.cpp

if HAVE_ZLIB_INSTALLED
libglobe_la_SOURCES += src/globe/minizip/ioapi.c
libglobe_la_SOURCES += src/globe/minizip/unzip.c
libglobe_la_SOURCES += src/globe/minizip/crypt.h
libglobe_la_SOURCES += src/globe/minizip/ioapi.h
libglobe_la_SOURCES += src/globe/minizip/unzip.h
endif

libglobe_la_HEADERS  = src/globe/dem.h                
libglobe_la_SOURCES += src/globe/dems_tcl.h           
libglobe_la_HEADERS += src/globe/dem_internal.h       
libglobe_la_SOURCES += src/globe/dem_tcl.h            
libglobe_la_HEADERS += src/globe/f_dem.h              
libglobe_la_HEADERS += src/globe/globe.h              
libglobe_la_HEADERS += src/globe/globe_data_manager.h 
libglobe_la_HEADERS += src/globe/globe_surf_internal.h
libglobe_la_SOURCES += src/globe/globe_surf_tcl.h     
libglobe_la_SOURCES += src/globe/globe_ie.h           
libglobe_la_HEADERS += src/globe/globe_variables.h    
libglobe_la_HEADERS += src/globe/shortmrf.h
                                 
libglobe_la_LIBADD = $(LIBS_SURFIT) $(TCLLIB) libsstuff.la libsurfit.la
if HAVE_ZLIB_INSTALLED
libglobe_la_LIBADD += -lz
endif 
libglobe_la_LDFLAGS = -version-info 2:1:0 -no-undefined --dllname libglobe.dll

dist-hook:

	chmod ugo+x install-sh
	rm -rf `find $(distdir) -name CVS`; \
	rm -rf `find $(distdir) -name "*.log"`; \
	rm -rf `find $(distdir) -name "*.dat"`; \
	rm -rf `find $(distdir) -name "core*"` 

install-data-hook:

	if ! test -d "$(DESTDIR)$(prefix)/share"; then \
		mkdir $(DESTDIR)$(prefix)/share; \
	fi; \
	if ! test -d "$(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)"; then \
		mkdir $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION); \
	fi; \
	if test -d "$(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/doc"; then \
		rm -rf $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/doc; \
	fi; \
	cp -r doc/html $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/doc ; \
	if test -d "$(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples"; then \
		rm -rf $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples; \
	fi; \
	mkdir $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples
	cp -r examples/surfit/ $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples/surfit; \
	cp -r examples/freeflow $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples/freeflow; \
	cp -r examples/globe $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/examples/globe; \
	rm -rf `find $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION) -name CVS`; \
	rm -rf `find $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION) -name "core*"`; \
	rm -rf `find $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION) -name "*.log"`; \
	rm -rf `find $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION) -name "*.dat"` 

uninstall-hook:

	if test -d "$(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)"; then \
		rm $(DESTDIR)$(prefix)/share/$(PACKAGE)-$(VERSION)/ -rf; \
	fi; \
	if test -f "$(DESTDIR)$(bindir)/cygsstuff-2.dll"; then \
		rm $(DESTDIR)$(bindir)/cygsstuff-2.dll; \
	fi; \
	if test -f "$(DESTDIR)$(bindir)/cygsurfit-2.dll"; then \
		rm $(DESTDIR)$(bindir)/cygsurfit-2.dll; \
	fi; \
	if test -f "$(DESTDIR)$(bindir)/cygfreeflow-2.dll"; then \
		rm $(DESTDIR)$(bindir)/cygfreeflow-2.dll; \
	fi; \
	if test -f "$(DESTDIR)$(bindir)/cygglobe-2.dll"; then \
		rm $(DESTDIR)$(bindir)/cygglobe-2.dll;
	fi

install-exec-hook:

	if test -f $(DESTDIR)$(bindir)/cygsstuff-2.dll; then \
		rm -f $(DESTDIR)$(bindir)/libsstuff.dll; \
		ln $(DESTDIR)$(bindir)/cygsstuff-2.dll $(DESTDIR)$(bindir)/libsstuff.dll; \
	fi

	if test -f $(DESTDIR)$(bindir)/cygsurfit-2.dll; then \
		rm -f $(DESTDIR)$(bindir)/libsurfit.dll; \
		ln $(DESTDIR)$(bindir)/cygsurfit-2.dll $(DESTDIR)$(bindir)/libsurfit.dll; \
	fi

if MAKE_FREEFLOW
	if test -f $(DESTDIR)$(bindir)/cygfreeflow-2.dll; then \
		rm -f $(DESTDIR)$(bindir)/libfreeflow.dll; \
		ln $(DESTDIR)$(bindir)/cygfreeflow-2.dll $(DESTDIR)$(bindir)/libfreeflow.dll; \
	fi
endif

if MAKE_GLOBE
	if test -f $(DESTDIR)$(bindir)/cygglobe-2.dll; then \
		rm -f $(DESTDIR)$(bindir)/libglobe.dll; \
		ln $(DESTDIR)$(bindir)/cygglobe-2.dll $(DESTDIR)$(bindir)/libglobe.dll; \
	fi
endif

