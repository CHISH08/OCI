cmake_minimum_required(VERSION 3.5)

project(5lab)

set(LIB_PRINT_TYPE "DEFAULT")

# set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

# set(CMAKE_CXX_FLAGS "$CMAKE_CXX_FLAGS -Wall")

file(GLOB 
    CPPS "./src2/*.cpp"
)

configure_file(
    "${PROJECT_SOURCE_DIR}/include/version.h.in"
    "${PROJECT_BINARY_DIR}/version.h"
)
include(GenerateExportHeader)
add_library(1 SHARED "${PROJECT_SOURCE_DIR}/src2/lib1.cpp" "${PROJECT_SOURCE_DIR}/include/math1.h")
generate_export_header(1)
target_include_directories(1 PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

include(GenerateExportHeader)
add_library(2 SHARED "${PROJECT_SOURCE_DIR}/src2/lib2.cpp" "${PROJECT_SOURCE_DIR}/include/math2.h")
generate_export_header(2)
target_include_directories(2 PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_BINARY_DIR}")

add_executable(${PROJECT_NAME} ${CPPS})