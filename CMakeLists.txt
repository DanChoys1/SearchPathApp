cmake_minimum_required(VERSION 3.5)

project(SearchPathApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(SearchPathApp
    main.cpp
    search_path_window.h
    search_path_window.cpp
    search_path_window.ui
    map_gr_item.h
    map_gr_item.cpp
    search_path_gr_scene.h
    search_path_gr_scene.cpp
    breadth_first_search_worker.h
    breadth_first_search_worker.cpp
    worker.h
    worker.cpp
    generate_map_worker.h
    generate_map_worker.cpp
    wheel_scale_gr_view.h
    wheel_scale_gr_view.cpp
)

target_link_libraries(SearchPathApp PRIVATE Qt5::Widgets)
