cmake_minimum_required(VERSION 3.12)
project(finalProject)
set (EXE_NAME finalProject)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -g")

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "graphData1.txt")
set (input02 "graphData2.txt")
set (input03 "graphData3.txt")

set (output01 "results1.txt")
set (output01 "results2.txt")
set (output01 "results3.txt")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 output01)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME} main.cpp graphData1.txt graphData2.txt graphData3.txt graph.h graph.cpp results1.txt results2.txt results3.txt)
