cmake_minimum_required(VERSION 2.8.9)
project(Toolbox-OOP)
 
include_directories(include/ include/sigpack/)
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(driver.out ${SOURCES})
target_compile_options(driver.out PUBLIC -Dunix -std=c++17 -m64 -g)
target_link_libraries(driver.out PUBLIC -larmadillo)
