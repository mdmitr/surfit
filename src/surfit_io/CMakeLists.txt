SET( PROJ_NAME libsurfit_io ) 

PROJECT( ${PROJ_NAME} )

FILE(GLOB_RECURSE srcs_cpp src/*.c*)
FILE(GLOB_RECURSE hdrs src/*.h*)


#
# includes
#
set (INCL_DIRS 	${TCL_INCLUDE_PATH}
		src
		${CMAKE_BINARY_DIR}
		../sstuff/src
		../surfit/src
)

if (JPEG_FOUND)
	set(INCL_DIRS ${INCL_DIRS} ${JPEG_INCLUDE_DIR})
endif()

include_directories( ${INCL_DIRS} )

#
# shared libs
#

add_library(${PROJ_NAME} SHARED ${srcs_cpp} ${hdrs})

set(LINK_LIBS ${PROJ_NAME} ${TCL_LIBRARY} libsstuff libsurfit)

if (JPEG_FOUND)
	set(LINK_LIBS ${LINK_LIBS} ${JPEG_LIBRARY})
endif()

target_link_libraries(${LINK_LIBS})

set_target_properties( ${PROJ_NAME} PROPERTIES PREFIX "" )

#
# install
#

install(TARGETS ${PROJ_NAME} DESTINATION lib)
