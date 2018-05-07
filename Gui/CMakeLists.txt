add_executable(tfill_gui time_filling gui controls)

find_package(Qt5 CONFIG REQUIRED Widgets Gui)
target_link_libraries(tfill_gui tfill_pathfinder Qt5::Widgets Qt5::Gui)
