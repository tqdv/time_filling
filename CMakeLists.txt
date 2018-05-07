cmake_minimum_required(VERSION 3.11)
project("time_filling" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TFILL_GUI "Enables the GUI" OFF)

if(TFILL_GUI)
	add_definitions(-DTFILL_GUI)
endif ()

if (CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion")
endif ()

set(CMAKE_AUTOMOC ON)

add_executable(tfill)
target_sources(tfill PRIVATE src/hexagon src/time_filling src/gui src/controls)
target_include_directories(tfill PRIVATE src)

find_package(Qt5 CONFIG REQUIRED Widgets Gui)
target_link_libraries(tfill Qt5::Widgets Qt5::Gui)

