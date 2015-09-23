SET( PROJ_NAME surfit_cmd ) 

PROJECT( ${PROJ_NAME} )

FILE(GLOB_RECURSE srcs_cpp src/*.cpp)
FILE(GLOB_RECURSE hdrs src/*.h*)

include_directories(
${TCL_INCLUDE_PATH}
src
${CMAKE_BINARY_DIR}
../sstuff/src
)


add_executable(${PROJ_NAME} ${srcs_cpp}  ${hdrs} )

target_link_libraries(${PROJ_NAME}
${TCL_LIBRARY}
)


