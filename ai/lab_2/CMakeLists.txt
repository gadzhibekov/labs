cmake_minimum_required(VERSION 3.10)

project(lab_2 VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
 
find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)

include_directories(src)

set(PROJECT_SOURCES

    src/main.cpp
    src/main_window.cpp
    src/game.cpp
    src/second_window.cpp
    src/dialog_window.cpp
    src/params.cpp
    src/ui/color.cpp
    src/ui/item.cpp
    src/ui/button.cpp
    src/ui/text.cpp
    src/ui/text_edit.cpp
    src/log/log.cpp


    src/main_window.h
    src/game.h
    src/second_window.h
    src/dialog_window.h
    src/params.h
    src/ui/color.h
    src/ui/item.h
    src/ui/button.h
    src/ui/text.h
    src/ui/text_edit.h
    src/log/log.h
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)