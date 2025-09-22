cmake_minimum_required(VERSION 3.10)

project(lab_1 VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
 
find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)

include_directories(src)

set(SOURCES
    src/main.cpp
    src/main_window.cpp
    src/player.cpp
    src/game.cpp
    src/log/log.cpp
    src/ui/field_button.cpp
    src/ui/icon.cpp
)

set(HEADERS
    src/main_window.h
    src/game.h
    src/log/log.h
    src/ui/field_button.h
    src/ui/icon.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)