cmake_minimum_required(VERSION 3.11)
project("time_filling" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TFILL_GUI "Enables the GUI" OFF)

if (CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion")
endif ()

set(CMAKE_AUTOMOC ON)

add_subdirectory(Pathfinder)
if(TFILL_GUI)
add_subdirectory(Gui)
endif()
add_subdirectory(Cli)
