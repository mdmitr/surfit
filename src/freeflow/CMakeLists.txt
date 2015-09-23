SET( PROJ_NAME libfreeflow ) 

PROJECT( ${PROJ_NAME} )

FILE(GLOB_RECURSE srcs_cpp src/*.c*)
FILE(GLOB_RECURSE hdrs src/*.h*)


include_directories(
	${TCL_INCLUDE_PATH}
	src
	${CMAKE_BINARY_DIR}
	../sstuff/src
	../surfit/src
)
                       
add_library(${PROJ_NAME} SHARED ${srcs_cpp} ${hdrs})

target_link_libraries(${PROJ_NAME}
	${TCL_LIBRARY}
	libsstuff
	libsurfit
)

