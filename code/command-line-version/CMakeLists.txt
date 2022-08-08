cmake_minimum_required(VERSION 3.22) 

# set the project name 
project(warehouseMgrSys VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable 
add_executable(warehouseMgrSys main.cpp warehouse.cpp )

configure_file(warehouseMgrSysConfig.h.in warehouseMgrSysConfig.h)
target_include_directories(warehouseMgrSys PUBLIC 
                            "${PROJECT_BINARY_DIR}"
                            "${PROJECT_SOURCE_DIR}")
