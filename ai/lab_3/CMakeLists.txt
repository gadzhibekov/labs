cmake_minimum_required(VERSION 3.10)

project(lab_3 VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
 
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

include_directories(src)

set(SOURCES
    src/main.cpp
    src/main_window.cpp
    src/game.cpp
    src/ui/button.cpp
    src/ui/map_item.cpp
    src/ui/text_item.cpp
)

set(HEADERS
    src/main_window.h
    src/game.h
    src/ui/button.h
    src/ui/map_item.h
    src/ui/text_item.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)