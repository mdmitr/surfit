AUTOMAKE_OPTIONS = foreign

$(OBJECTS): libtool
libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck

INCLUDES = $(TCLINCLUDE) $(FLTK_INCLUDE) -Isurfit/src -Ifreeflow/src -Ibula/src
EXTRA_DIST = vc6/*
EXTRA_DIST += surfit/src/config.h
EXTRA_DIST += surfit/src/interface/*.i
EXTRA_DIST += surfit/examples/*
EXTRA_DIST += surfit/doc/*
EXTRA_DIST += surfit/lib/*
EXTRA_DIST += freeflow/src/interface/*.i
EXTRA_DIST += freeflow/examples/*
EXTRA_DIST += freeflow/doc/*
EXTRA_DIST += globe/src/interface/*.i
EXTRA_DIST += globe/doc/*
EXTRA_DIST += bula/src/*.ico
EXTRA_DIST += bula/src/*.rc
EXTRA_DIST += bula/doc/*
EXTRA_DIST += funner2d/doc/*
EXTRA_DIST += doc/*
EXTRA_DIST += m/*
EXTRA_DIST += html/*
EXTRA_DIST += nsi/*
EXTRA_DIST += clean.bat

#CXXFLAGS = -ggdb  -mwindows -DWIN32
#CXXFLAGS = -O2

# Build a libtool library, surfit.la for installation in libdir.
#if TCL
lib_LTLIBRARIES = libsurfit.la 

if MAKE_FREEFLOW
lib_LTLIBRARIES += libfreeflow.la 
endif

if MAKE_GLOBE
lib_LTLIBRARIES += libglobe.la 
endif

bin_PROGRAMS = 

if MAKE_FUNNER
bin_PROGRAMS += funner
endif

if MAKE_BULA
bin_PROGRAMS += Bula
endif


libsurfit_la_SOURCES =  surfit/src/area.cpp                                       
libsurfit_la_SOURCES += surfit/src/areas.cpp                                      
libsurfit_la_SOURCES += surfit/src/area_internal.cpp                              
libsurfit_la_SOURCES += surfit/src/area_tcl.cpp                                   
libsurfit_la_SOURCES += surfit/src/area_show.cpp                                   
libsurfit_la_SOURCES += surfit/src/area_user.cpp                                  
libsurfit_la_SOURCES += surfit/src/boolvec.cpp                                    
libsurfit_la_SOURCES += surfit/src/cntr.cpp                                       
libsurfit_la_SOURCES += surfit/src/cntrs.cpp                                      
libsurfit_la_SOURCES += surfit/src/cntr_internal.cpp                              
libsurfit_la_SOURCES += surfit/src/cntr_tcl.cpp                                   
libsurfit_la_SOURCES += surfit/src/cntr_show.cpp                                   
libsurfit_la_SOURCES += surfit/src/cntr_user.cpp                                  
libsurfit_la_SOURCES += surfit/src/colors.cpp                                     
libsurfit_la_SOURCES += surfit/src/color_scale.cpp                                
libsurfit_la_SOURCES += surfit/src/completer.cpp                                  
libsurfit_la_SOURCES += surfit/src/completer_tcl.cpp                              
libsurfit_la_SOURCES += surfit/src/completer_user.cpp                             
libsurfit_la_SOURCES += surfit/src/conrec.cxx                                     
libsurfit_la_SOURCES += surfit/src/curv.cpp                                       
libsurfit_la_SOURCES += surfit/src/curvs.cpp                                      
libsurfit_la_SOURCES += surfit/src/curv_internal.cpp                              
libsurfit_la_SOURCES += surfit/src/curv_show.cpp                                  
libsurfit_la_SOURCES += surfit/src/curv_tcl.cpp                                   
libsurfit_la_SOURCES += surfit/src/curv_user.cpp                                  
libsurfit_la_SOURCES += surfit/src/data.cpp                                       
libsurfit_la_SOURCES += surfit/src/datafile.cpp                                   
libsurfit_la_SOURCES += surfit/src/defarea.cpp                                    
libsurfit_la_SOURCES += surfit/src/defareas.cpp                                   
libsurfit_la_SOURCES += surfit/src/defarea_internal.cpp                           
libsurfit_la_SOURCES += surfit/src/defarea_show.cpp                               
libsurfit_la_SOURCES += surfit/src/defarea_tcl.cpp                                
libsurfit_la_SOURCES += surfit/src/defarea_user.cpp                               
libsurfit_la_SOURCES += surfit/src/draw.cpp                                       
libsurfit_la_SOURCES += surfit/src/draw_object.cpp                                
libsurfit_la_SOURCES += surfit/src/dynamic.cpp                                    
libsurfit_la_SOURCES += surfit/src/dynamics.cpp                                   
libsurfit_la_SOURCES += surfit/src/dynamic_internal.cpp                           
libsurfit_la_SOURCES += surfit/src/dynamic_tcl.cpp                                
libsurfit_la_SOURCES += surfit/src/dynamic_user.cpp                               
libsurfit_la_SOURCES += surfit/src/fileio.cpp                                     
libsurfit_la_SOURCES += surfit/src/file_manager.cpp                               
libsurfit_la_SOURCES += surfit/src/fill_with.cpp                                  
libsurfit_la_SOURCES += surfit/src/fill_with_tcl.cpp                              
libsurfit_la_SOURCES += surfit/src/fill_with_user.cpp                             
libsurfit_la_SOURCES += surfit/src/flt.cpp                                        
libsurfit_la_SOURCES += surfit/src/flts.cpp                                       
libsurfit_la_SOURCES += surfit/src/flt_internal.cpp                               
libsurfit_la_SOURCES += surfit/src/flt_tcl.cpp                                    
libsurfit_la_SOURCES += surfit/src/flt_show.cpp                                    
libsurfit_la_SOURCES += surfit/src/flt_user.cpp                                   
libsurfit_la_SOURCES += surfit/src/func.cpp                                       
libsurfit_la_SOURCES += surfit/src/funcs.cpp                                      
libsurfit_la_SOURCES += surfit/src/func_internal.cpp                              
libsurfit_la_SOURCES += surfit/src/func_show.cpp                                  
libsurfit_la_SOURCES += surfit/src/func_tcl.cpp                                   
libsurfit_la_SOURCES += surfit/src/func_user.cpp                                  
libsurfit_la_SOURCES += surfit/src/geom_alg.cpp                                   
libsurfit_la_SOURCES += surfit/src/grid.cpp                                       
libsurfit_la_SOURCES += surfit/src/grid_internal.cpp                              
libsurfit_la_SOURCES += surfit/src/grid_line.cpp                                  
libsurfit_la_SOURCES += surfit/src/grid_line_internal.cpp                         
libsurfit_la_SOURCES += surfit/src/grid_line_tcl.cpp                              
libsurfit_la_SOURCES += surfit/src/grid_line_user.cpp                             
libsurfit_la_SOURCES += surfit/src/grid_show.cpp                                  
libsurfit_la_SOURCES += surfit/src/grid_tcl.cpp                                   
libsurfit_la_SOURCES += surfit/src/grid_user.cpp                                  
libsurfit_la_SOURCES += surfit/src/intvec.cpp                                     
libsurfit_la_SOURCES += surfit/src/iso.cpp                                        
libsurfit_la_SOURCES += surfit/src/isos.cpp                                       
libsurfit_la_SOURCES += surfit/src/iso_internal.cpp                               
libsurfit_la_SOURCES += surfit/src/iso_tcl.cpp                                    
libsurfit_la_SOURCES += surfit/src/iso_show.cpp                                    
libsurfit_la_SOURCES += surfit/src/iso_user.cpp                                   
libsurfit_la_SOURCES += surfit/src/license.cpp                                    
libsurfit_la_SOURCES += surfit/src/main_method.cpp                                
libsurfit_la_SOURCES += surfit/src/matlab.cpp                                     
libsurfit_la_SOURCES += surfit/src/mrf.cpp                                        
libsurfit_la_SOURCES += surfit/src/oper.cpp                                       
libsurfit_la_SOURCES += surfit/src/operD1.cpp                                     
libsurfit_la_SOURCES += surfit/src/operD1_rect.cpp                                
libsurfit_la_SOURCES += surfit/src/operD2.cpp                                     
libsurfit_la_SOURCES += surfit/src/operD2_rect.cpp                                
libsurfit_la_SOURCES += surfit/src/oper_points.cpp                                
libsurfit_la_SOURCES += surfit/src/points.cpp                                     
libsurfit_la_SOURCES += surfit/src/projector.cpp                                  
libsurfit_la_SOURCES += surfit/src/read_txt.cpp                                   
libsurfit_la_SOURCES += surfit/src/rnd.cpp                                        
libsurfit_la_SOURCES += surfit/src/sort_alg.cpp                                   
libsurfit_la_SOURCES += surfit/src/surfit.cpp                                     
libsurfit_la_SOURCES += surfit/src/surfit_wrap.cxx                                
libsurfit_la_SOURCES += surfit/src/task.cpp                                       
libsurfit_la_SOURCES += surfit/src/tasks.cpp                                      
libsurfit_la_SOURCES += surfit/src/task_internal.cpp                              
libsurfit_la_SOURCES += surfit/src/task_show.cpp                                  
libsurfit_la_SOURCES += surfit/src/task_tcl.cpp                                   
libsurfit_la_SOURCES += surfit/src/task_user.cpp                                  
libsurfit_la_SOURCES += surfit/src/trackball.cpp                                  
libsurfit_la_SOURCES += surfit/src/trend.cpp                                      
libsurfit_la_SOURCES += surfit/src/trends.cpp                                     
libsurfit_la_SOURCES += surfit/src/trend_internal.cpp                             
libsurfit_la_SOURCES += surfit/src/trend_show.cpp                                 
libsurfit_la_SOURCES += surfit/src/trend_tcl.cpp                                  
libsurfit_la_SOURCES += surfit/src/trend_user.cpp                                 
libsurfit_la_SOURCES += surfit/src/user.cpp                                       
libsurfit_la_SOURCES += surfit/src/variables.cpp                                  
libsurfit_la_SOURCES += surfit/src/vec.cpp                                        
libsurfit_la_SOURCES += surfit/src/vec_alg.cpp                                    
libsurfit_la_SOURCES += surfit/src/warea.cpp                                      
libsurfit_la_SOURCES += surfit/src/wareas.cpp                                     
libsurfit_la_SOURCES += surfit/src/warea_internal.cpp                             
libsurfit_la_SOURCES += surfit/src/warea_tcl.cpp                                  
libsurfit_la_SOURCES += surfit/src/warea_show.cpp                                  
libsurfit_la_SOURCES += surfit/src/warea_user.cpp                                 
libsurfit_la_SOURCES += surfit/src/wcntr.cpp                                      
libsurfit_la_SOURCES += surfit/src/wcntrs.cpp                                     
libsurfit_la_SOURCES += surfit/src/wcntr_internal.cpp                             
libsurfit_la_SOURCES += surfit/src/wcntr_tcl.cpp                                  
libsurfit_la_SOURCES += surfit/src/wcntr_show.cpp                                  
libsurfit_la_SOURCES += surfit/src/wcntr_user.cpp                                 
libsurfit_la_SOURCES += surfit/src/wfunc.cpp                                      
libsurfit_la_SOURCES += surfit/src/wfuncs.cpp                                     
libsurfit_la_SOURCES += surfit/src/wfunc_internal.cpp                             
libsurfit_la_SOURCES += surfit/src/wfunc_show.cpp                                 
libsurfit_la_SOURCES += surfit/src/wfunc_tcl.cpp                                  
libsurfit_la_SOURCES += surfit/src/wfunc_user.cpp                                 
libsurfit_la_SOURCES += surfit/src/wiso.cpp                                       
libsurfit_la_SOURCES += surfit/src/wisos.cpp                                      
libsurfit_la_SOURCES += surfit/src/wiso_internal.cpp                              
libsurfit_la_SOURCES += surfit/src/wiso_tcl.cpp                                   
libsurfit_la_SOURCES += surfit/src/wiso_show.cpp                                   
libsurfit_la_SOURCES += surfit/src/wiso_user.cpp                                  
libsurfit_la_SOURCES += surfit/src/wtask.cpp                                      
libsurfit_la_SOURCES += surfit/src/wtasks.cpp                                     
libsurfit_la_SOURCES += surfit/src/wtask_internal.cpp                             
libsurfit_la_SOURCES += surfit/src/wtask_show.cpp                                 
libsurfit_la_SOURCES += surfit/src/wtask_tcl.cpp                                  
libsurfit_la_SOURCES += surfit/src/wtask_user.cpp                                 



libsurfit_la_SOURCES += surfit/src/area.h                                   
libsurfit_la_SOURCES += surfit/src/areas.h                                  
libsurfit_la_SOURCES += surfit/src/area_internal.h                          
libsurfit_la_SOURCES += surfit/src/area_tcl.h                               
libsurfit_la_SOURCES += surfit/src/area_show.h                               
libsurfit_la_SOURCES += surfit/src/area_user.h                              
libsurfit_la_SOURCES += surfit/src/bitvec.h                                 
libsurfit_la_SOURCES += surfit/src/bitvec_alg.h                             
libsurfit_la_SOURCES += surfit/src/boolvec.h                                
libsurfit_la_SOURCES += surfit/src/cg.h                                     
libsurfit_la_SOURCES += surfit/src/cg2.h                                    
libsurfit_la_SOURCES += surfit/src/cntr.h                                   
libsurfit_la_SOURCES += surfit/src/cntrs.h                                  
libsurfit_la_SOURCES += surfit/src/cntr_internal.h                          
libsurfit_la_SOURCES += surfit/src/cntr_tcl.h                               
libsurfit_la_SOURCES += surfit/src/cntr_show.h                               
libsurfit_la_SOURCES += surfit/src/cntr_user.h                              
libsurfit_la_SOURCES += surfit/src/colors.h                                 
libsurfit_la_SOURCES += surfit/src/color_scale.h                            
libsurfit_la_SOURCES += surfit/src/completer.h                              
libsurfit_la_SOURCES += surfit/src/completer_tcl.h                          
libsurfit_la_SOURCES += surfit/src/completer_user.h                         
libsurfit_la_SOURCES += surfit/src/config.h                                 
libsurfit_la_SOURCES += surfit/src/curv.h                                   
libsurfit_la_SOURCES += surfit/src/curvs.h                                  
libsurfit_la_SOURCES += surfit/src/curv_internal.h                          
libsurfit_la_SOURCES += surfit/src/curv_show.h                              
libsurfit_la_SOURCES += surfit/src/curv_tcl.h                               
libsurfit_la_SOURCES += surfit/src/curv_user.h                              
libsurfit_la_SOURCES += surfit/src/data.h                                   
libsurfit_la_SOURCES += surfit/src/datafile.h                               
libsurfit_la_SOURCES += surfit/src/defarea.h                                
libsurfit_la_SOURCES += surfit/src/defareas.h                               
libsurfit_la_SOURCES += surfit/src/defarea_internal.h                       
libsurfit_la_SOURCES += surfit/src/defarea_show.h                           
libsurfit_la_SOURCES += surfit/src/defarea_tcl.h                            
libsurfit_la_SOURCES += surfit/src/defarea_user.h                           
libsurfit_la_SOURCES += surfit/src/draw.h                                   
libsurfit_la_SOURCES += surfit/src/draw_object.h                            
libsurfit_la_SOURCES += surfit/src/dynamic.h                                
libsurfit_la_SOURCES += surfit/src/dynamics.h                               
libsurfit_la_SOURCES += surfit/src/dynamic_internal.h                       
libsurfit_la_SOURCES += surfit/src/dynamic_tcl.h                            
libsurfit_la_SOURCES += surfit/src/dynamic_user.h                           
libsurfit_la_SOURCES += surfit/src/fileio.h                                 
libsurfit_la_SOURCES += surfit/src/file_manager.h                           
libsurfit_la_SOURCES += surfit/src/fill_with.h                              
libsurfit_la_SOURCES += surfit/src/fill_with_tcl.h                          
libsurfit_la_SOURCES += surfit/src/fill_with_user.h                         
libsurfit_la_SOURCES += surfit/src/flt.h                                    
libsurfit_la_SOURCES += surfit/src/flts.h                                   
libsurfit_la_SOURCES += surfit/src/flt_internal.h                           
libsurfit_la_SOURCES += surfit/src/flt_tcl.h                                
libsurfit_la_SOURCES += surfit/src/flt_show.h                                
libsurfit_la_SOURCES += surfit/src/flt_user.h                               
libsurfit_la_SOURCES += surfit/src/free_elements.h                          
libsurfit_la_SOURCES += surfit/src/func.h                                   
libsurfit_la_SOURCES += surfit/src/funcs.h                                  
libsurfit_la_SOURCES += surfit/src/func_internal.h                          
libsurfit_la_SOURCES += surfit/src/func_show.h                              
libsurfit_la_SOURCES += surfit/src/func_tcl.h                               
libsurfit_la_SOURCES += surfit/src/func_user.h                              
libsurfit_la_SOURCES += surfit/src/geom_alg.h                               
libsurfit_la_SOURCES += surfit/src/grid.h                                   
libsurfit_la_SOURCES += surfit/src/grid_internal.h                          
libsurfit_la_SOURCES += surfit/src/grid_line.h                              
libsurfit_la_SOURCES += surfit/src/grid_line_internal.h                     
libsurfit_la_SOURCES += surfit/src/grid_line_tcl.h                          
libsurfit_la_SOURCES += surfit/src/grid_line_user.h                         
libsurfit_la_SOURCES += surfit/src/grid_show.h                              
libsurfit_la_SOURCES += surfit/src/grid_tcl.h                               
libsurfit_la_SOURCES += surfit/src/grid_user.h                              
libsurfit_la_SOURCES += surfit/src/ie.h                                     
libsurfit_la_SOURCES += surfit/src/intvec.h                                 
libsurfit_la_SOURCES += surfit/src/iso.h                                    
libsurfit_la_SOURCES += surfit/src/isos.h                                   
libsurfit_la_SOURCES += surfit/src/iso_internal.h                           
libsurfit_la_SOURCES += surfit/src/iso_tcl.h                                
libsurfit_la_SOURCES += surfit/src/iso_show.h                                
libsurfit_la_SOURCES += surfit/src/iso_user.h                               
libsurfit_la_SOURCES += surfit/src/jacobi.h                                 
libsurfit_la_SOURCES += surfit/src/license.h                                
libsurfit_la_SOURCES += surfit/src/main_method.h                            
libsurfit_la_SOURCES += surfit/src/matfile.h                                
libsurfit_la_SOURCES += surfit/src/matlab.h                                 
libsurfit_la_SOURCES += surfit/src/mrf.h                                    
libsurfit_la_SOURCES += surfit/src/oper.h                                   
libsurfit_la_SOURCES += surfit/src/operD1.h                                 
libsurfit_la_SOURCES += surfit/src/operD2.h                                 
libsurfit_la_SOURCES += surfit/src/oper_points.h                            
libsurfit_la_SOURCES += surfit/src/points.h                                 
libsurfit_la_SOURCES += surfit/src/projector.h                              
libsurfit_la_SOURCES += surfit/src/read_txt.h                               
libsurfit_la_SOURCES += surfit/src/real.h                                   
libsurfit_la_SOURCES += surfit/src/rnd.h                                    
libsurfit_la_SOURCES += surfit/src/simpiter.h                               
libsurfit_la_SOURCES += surfit/src/simpiter2.h                              
libsurfit_la_SOURCES += surfit/src/solvers.h                                
libsurfit_la_SOURCES += surfit/src/sor.h                                    
libsurfit_la_SOURCES += surfit/src/sort_alg.h                               
libsurfit_la_SOURCES += surfit/src/ssor.h                                   
libsurfit_la_SOURCES += surfit/src/surfit.h                                 
libsurfit_la_SOURCES += surfit/src/task.h                                   
libsurfit_la_SOURCES += surfit/src/tasks.h                                  
libsurfit_la_SOURCES += surfit/src/task_internal.h                          
libsurfit_la_SOURCES += surfit/src/task_show.h                              
libsurfit_la_SOURCES += surfit/src/task_tcl.h                               
libsurfit_la_SOURCES += surfit/src/task_user.h                              
libsurfit_la_SOURCES += surfit/src/trackball.h                              
libsurfit_la_SOURCES += surfit/src/trend.h                                  
libsurfit_la_SOURCES += surfit/src/trends.h                                 
libsurfit_la_SOURCES += surfit/src/trend_internal.h                         
libsurfit_la_SOURCES += surfit/src/trend_show.h                             
libsurfit_la_SOURCES += surfit/src/trend_tcl.h                              
libsurfit_la_SOURCES += surfit/src/trend_user.h                             
libsurfit_la_SOURCES += surfit/src/user.h                                   
libsurfit_la_SOURCES += surfit/src/variables.h                              
libsurfit_la_SOURCES += surfit/src/variables_internal.h                     
libsurfit_la_SOURCES += surfit/src/variables_tcl.h                          
libsurfit_la_SOURCES += surfit/src/vec.h                                    
libsurfit_la_SOURCES += surfit/src/vec_alg.h                                
libsurfit_la_SOURCES += surfit/src/warea.h                                  
libsurfit_la_SOURCES += surfit/src/wareas.h                                 
libsurfit_la_SOURCES += surfit/src/warea_internal.h                         
libsurfit_la_SOURCES += surfit/src/warea_tcl.h                              
libsurfit_la_SOURCES += surfit/src/warea_show.h                              
libsurfit_la_SOURCES += surfit/src/warea_user.h                             
libsurfit_la_SOURCES += surfit/src/wcntr.h                                  
libsurfit_la_SOURCES += surfit/src/wcntrs.h                                 
libsurfit_la_SOURCES += surfit/src/wcntr_internal.h                         
libsurfit_la_SOURCES += surfit/src/wcntr_tcl.h                              
libsurfit_la_SOURCES += surfit/src/wcntr_show.h                              
libsurfit_la_SOURCES += surfit/src/wcntr_user.h                             
libsurfit_la_SOURCES += surfit/src/wfunc.h                                  
libsurfit_la_SOURCES += surfit/src/wfuncs.h                                 
libsurfit_la_SOURCES += surfit/src/wfunc_internal.h                         
libsurfit_la_SOURCES += surfit/src/wfunc_show.h                             
libsurfit_la_SOURCES += surfit/src/wfunc_tcl.h                              
libsurfit_la_SOURCES += surfit/src/wfunc_user.h                             
libsurfit_la_SOURCES += surfit/src/wiso.h                                   
libsurfit_la_SOURCES += surfit/src/wisos.h                                  
libsurfit_la_SOURCES += surfit/src/wiso_internal.h                          
libsurfit_la_SOURCES += surfit/src/wiso_tcl.h                               
libsurfit_la_SOURCES += surfit/src/wiso_show.h                               
libsurfit_la_SOURCES += surfit/src/wiso_user.h                              
libsurfit_la_SOURCES += surfit/src/wtask.h                                  
libsurfit_la_SOURCES += surfit/src/wtasks.h                                 
libsurfit_la_SOURCES += surfit/src/wtask_internal.h                         
libsurfit_la_SOURCES += surfit/src/wtask_show.h                             
libsurfit_la_SOURCES += surfit/src/wtask_tcl.h                              
libsurfit_la_SOURCES += surfit/src/wtask_user.h                             


                            
libsurfit_la_LIBADD = $(LIBS_SURFIT) $(TCLLIB) $(GLLIB) $(FLTK_LIB) $(FLTK_GL_LIB)
libsurfit_la_LDFLAGS = -version-info 1:0:0 -no-undefined --dllname libsurfit.dll


libfreeflow_la_SOURCES  = freeflow/src/flow.cpp               
libfreeflow_la_SOURCES += freeflow/src/flow_colors.cpp 
libfreeflow_la_SOURCES += freeflow/src/flow_curv_show.cpp 
libfreeflow_la_SOURCES += freeflow/src/flow_file_manager.cpp  
libfreeflow_la_SOURCES += freeflow/src/flow_func_internal.cpp 
libfreeflow_la_SOURCES += freeflow/src/flow_func_tcl.cpp      
libfreeflow_la_SOURCES += freeflow/src/flow_variables.cpp     
libfreeflow_la_SOURCES += freeflow/src/freeflow.cpp           
libfreeflow_la_SOURCES += freeflow/src/freeflow_wrap.cxx      
libfreeflow_la_SOURCES += freeflow/src/lcm_simple.cpp         
libfreeflow_la_SOURCES += freeflow/src/lcm_simple_internal.cpp
libfreeflow_la_SOURCES += freeflow/src/lcm_simple_tcl.cpp     
libfreeflow_la_SOURCES += freeflow/src/lcm_simple_user.cpp    
libfreeflow_la_SOURCES += freeflow/src/parea.cpp              
libfreeflow_la_SOURCES += freeflow/src/pareas.cpp             
libfreeflow_la_SOURCES += freeflow/src/parea_internal.cpp     
libfreeflow_la_SOURCES += freeflow/src/parea_tcl.cpp          
libfreeflow_la_SOURCES += freeflow/src/parea_show.cpp          
libfreeflow_la_SOURCES += freeflow/src/parea_user.cpp         
libfreeflow_la_SOURCES += freeflow/src/pcntr.cpp              
libfreeflow_la_SOURCES += freeflow/src/pcntrs.cpp             
libfreeflow_la_SOURCES += freeflow/src/pcntr_internal.cpp     
libfreeflow_la_SOURCES += freeflow/src/pcntr_tcl.cpp          
libfreeflow_la_SOURCES += freeflow/src/pcntr_show.cpp          
libfreeflow_la_SOURCES += freeflow/src/pcntr_user.cpp         
libfreeflow_la_SOURCES += freeflow/src/piso.cpp               
libfreeflow_la_SOURCES += freeflow/src/pisos.cpp              
libfreeflow_la_SOURCES += freeflow/src/piso_internal.cpp      
libfreeflow_la_SOURCES += freeflow/src/piso_tcl.cpp           
libfreeflow_la_SOURCES += freeflow/src/piso_show.cpp           
libfreeflow_la_SOURCES += freeflow/src/piso_user.cpp          
libfreeflow_la_SOURCES += freeflow/src/ptask.cpp              
libfreeflow_la_SOURCES += freeflow/src/ptasks.cpp             
libfreeflow_la_SOURCES += freeflow/src/ptask_internal.cpp     
libfreeflow_la_SOURCES += freeflow/src/ptask_tcl.cpp          
libfreeflow_la_SOURCES += freeflow/src/ptask_show.cpp          
libfreeflow_la_SOURCES += freeflow/src/ptask_user.cpp

libfreeflow_la_SOURCES += freeflow/src/flow.h
libfreeflow_la_SOURCES += freeflow/src/flow_colors.h
libfreeflow_la_SOURCES += freeflow/src/flow_curv_show.h
libfreeflow_la_SOURCES += freeflow/src/flow_file_manager.h
libfreeflow_la_SOURCES += freeflow/src/flow_func_internal.h
libfreeflow_la_SOURCES += freeflow/src/flow_func_tcl.h
libfreeflow_la_SOURCES += freeflow/src/flow_ie.h
libfreeflow_la_SOURCES += freeflow/src/flow_variables.h
libfreeflow_la_SOURCES += freeflow/src/freeflow.h
libfreeflow_la_SOURCES += freeflow/src/lcm_simple.h
libfreeflow_la_SOURCES += freeflow/src/lcm_simple_internal.h
libfreeflow_la_SOURCES += freeflow/src/lcm_simple_tcl.h
libfreeflow_la_SOURCES += freeflow/src/lcm_simple_user.h
libfreeflow_la_SOURCES += freeflow/src/parea.h
libfreeflow_la_SOURCES += freeflow/src/pareas.h
libfreeflow_la_SOURCES += freeflow/src/parea_internal.h
libfreeflow_la_SOURCES += freeflow/src/parea_tcl.h
libfreeflow_la_SOURCES += freeflow/src/parea_show.h
libfreeflow_la_SOURCES += freeflow/src/parea_user.h
libfreeflow_la_SOURCES += freeflow/src/pcntr.h
libfreeflow_la_SOURCES += freeflow/src/pcntrs.h
libfreeflow_la_SOURCES += freeflow/src/pcntr_internal.h
libfreeflow_la_SOURCES += freeflow/src/pcntr_tcl.h
libfreeflow_la_SOURCES += freeflow/src/pcntr_show.h
libfreeflow_la_SOURCES += freeflow/src/pcntr_user.h
libfreeflow_la_SOURCES += freeflow/src/piso.h
libfreeflow_la_SOURCES += freeflow/src/pisos.h
libfreeflow_la_SOURCES += freeflow/src/piso_internal.h
libfreeflow_la_SOURCES += freeflow/src/piso_tcl.h
libfreeflow_la_SOURCES += freeflow/src/piso_show.h
libfreeflow_la_SOURCES += freeflow/src/piso_user.h
libfreeflow_la_SOURCES += freeflow/src/ptask.h
libfreeflow_la_SOURCES += freeflow/src/ptasks.h
libfreeflow_la_SOURCES += freeflow/src/ptask_internal.h
libfreeflow_la_SOURCES += freeflow/src/ptask_tcl.h
libfreeflow_la_SOURCES += freeflow/src/ptask_show.h
libfreeflow_la_SOURCES += freeflow/src/ptask_user.h
         

libfreeflow_la_LIBADD = $(LIBS_SURFIT) $(TCLLIB) $(GLLIB) $(FLTK_LIB) $(FLTK_GL_LIB) libsurfit.la
libfreeflow_la_LDFLAGS = -version-info 1:0:0 -no-undefined --dllname libfreeflow.dll


libglobe_la_SOURCES = globe/src/globe.cpp     
libglobe_la_SOURCES += globe/src/globe_wrap.cxx
libglobe_la_SOURCES += globe/src/globe.h
libglobe_la_SOURCES += globe/src/ie_globe.h

libglobe_la_LIBADD = $(LIBS_SURFIT) $(TCLLIB) libsurfit.la 
libglobe_la_LDFLAGS = -version-info 1:0:0 -no-undefined --dllname libglobe.dll

Bula_SOURCES  = bula/src/bula.cxx 
Bula_SOURCES += bula/src/bula_view.cxx
Bula_SOURCES += bula/src/bula_view.h
Bula_SOURCES += bula/src/ie_bula.h
Bula_SOURCES += bula/src/init_surfit.h
Bula_SOURCES += bula/src/resource.h

Bula_LDADD = $(GLLIB) $(FLTK_LIB) $(FLTK_GL_LIB) $(LIBS_SURFIT) $(TCLLIB)

funner_SOURCES  = funner2d/src/color_scale_dlg.cpp 
funner_SOURCES += funner2d/src/details_btn.cpp     
funner_SOURCES += funner2d/src/funner2d.cpp        
funner_SOURCES += funner2d/src/funner2d_cbs.cpp    
funner_SOURCES += funner2d/src/funner2d_cmds.cpp   
funner_SOURCES += funner2d/src/funner2d_mainwnd.cpp
funner_SOURCES += funner2d/src/funner_channel.cpp  
funner_SOURCES += funner2d/src/gl_view.cpp         

funner_SOURCES += funner2d/src/color_scale_dlg.h
funner_SOURCES += funner2d/src/defines.h
funner_SOURCES += funner2d/src/details_btn.h
funner_SOURCES += funner2d/src/funner2d_mainwnd.h
funner_SOURCES += funner2d/src/funner_channel.h
funner_SOURCES += funner2d/src/gl_view.h
funner_SOURCES += funner2d/src/gl_view_funner2d.h
funner_SOURCES += funner2d/src/ie_funner2d.h

funner_SOURCES += funner2d/src/gl_view_funner2d.cpp
funner_LDADD = $(GLLIB) $(FLTK_LIB) $(FLTK_GL_LIB) $(LIBS_SURFIT) $(TCLLIB)

install-exec-hook:

	if test -f $(DESTDIR)$(bindir)/cygsurfit-1.dll; then \
		rm -f $(DESTDIR)$(bindir)/libsurfit.dll; \
		ln $(DESTDIR)$(bindir)/cygsurfit-1.dll $(DESTDIR)$(bindir)/libsurfit.dll; \
	fi

if MAKE_FREEFLOW
	if test -f $(DESTDIR)$(bindir)/cygfreeflow-1.dll; then \
		rm -f $(DESTDIR)$(bindir)/libfreeflow.dll; \
		ln $(DESTDIR)$(bindir)/cygfreeflow-1.dll $(DESTDIR)$(bindir)/libfreeflow.dll; \
	fi
endif

if MAKE_GLOBE
	if test -f $(DESTDIR)$(bindir)/cygglobe-1.dll; then \
		rm -f $(DESTDIR)$(bindir)/libglobe.dll; \
		ln $(DESTDIR)$(bindir)/cygglobe-1.dll $(DESTDIR)$(bindir)/libglobe.dll; \
	fi
endif

