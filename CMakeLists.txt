cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0069 NEW)
project(fmo_solver)
link_libraries(-lpthread)
file(GLOB SourceFiles *.cpp)
add_executable(fmo_solver ${SourceFiles})
set_property(TARGET fmo_solver PROPERTY CXX_STANDARD 17)
set_property(TARGET fmo_solver PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
add_compile_definitions(VERSION="${VERSION}")
