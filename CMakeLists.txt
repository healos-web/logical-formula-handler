cmake_minimum_required(VERSION 3.14)
project(untitled)
#
#set(CMAKE_CXX_STANDARD 17)
#
#
find_package(Boost 1.65.1 COMPONENTS regex REQUIRED)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")
#
#set (Boost_USE_STATIC_LIBS OFF) # enable dynamic linking
#set (Boost_USE_MULTITHREAD ON)  # enable multithreading
#find_package (Boost COMPONENTS REQUIRED chrono filesystem)
#
#add_executable(untitled main.cpp)
#target_link_libraries (untitled ${Boost_LIBRARIES})
# see https://cmake.org/cmake/help/latest/module/FindBoost.html

#set(Boost_USE_STATIC_LIBS OFF) #enable dynamic linking
#set(BOOST_ROOT "/usr/local/Cellar/boost/1.65.1")
#
#find_package(Boost REQUIRED COMPONENTS components system filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_executable(untitled main.cpp)
target_link_libraries(untitled ${Boost_LIBRARIES})
