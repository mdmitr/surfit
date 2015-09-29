SET( PROJ_NAME libsurfit ) 

PROJECT( ${PROJ_NAME} )

FILE(GLOB_RECURSE srcs_cpp src/*.c*)
FILE(GLOB_RECURSE hdrs src/*.h*)

list(REMOVE_ITEM srcs_cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/matrD2_aniso.cpp)

include_directories(
	${TCL_INCLUDE_PATH}
	src
	${CMAKE_BINARY_DIR}
	../sstuff/src
	../sstuff/src/ptypes
)

#definitions for triangulation library
add_definitions(-DANSI_DECLARATORS -DNO_TIMER -DTRILIBRARY)

add_library(${PROJ_NAME} SHARED ${srcs_cpp} ${hdrs})

target_link_libraries(${PROJ_NAME}
	${TCL_LIBRARY}
	libsstuff
)

set_target_properties( ${PROJ_NAME} PROPERTIES PREFIX "" )

#
# Install section
#

install(TARGETS ${PROJ_NAME} DESTINATION lib)
