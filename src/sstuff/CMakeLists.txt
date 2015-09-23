SET( PROJ_NAME libsstuff ) 

PROJECT( ${PROJ_NAME} )

FILE(GLOB_RECURSE ptypes_headers src/ptypes/*.h*)
FILE(GLOB_RECURSE ptypes_src src/ptypes/*.c*)

source_group("ptypes" FILES ${ptypes_headers} ${ptypes_src} )

FILE(GLOB_RECURSE srcs_cpp src/*.cpp)
FILE(GLOB_RECURSE hdrs src/*.h*)

include_directories(
${TCL_INCLUDE_PATH}
src
src/ptypes
${CMAKE_BINARY_DIR}
)

add_library(${PROJ_NAME} SHARED ${srcs_cpp} ${hdrs} ${ptypes_src} )

target_link_libraries(${PROJ_NAME}
${TCL_LIBRARY}
)

