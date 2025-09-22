cmake_minimum_required(VERSION 3.10)

project(lab_5 VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
 
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(src)

set(SOURCES
    src/main.cpp
    src/main_window.cpp
    src/ui/button.cpp
    src/ui/pixel.cpp
    src/ui/color.cpp
    src/nn/neural.cpp
)

set(HEADERS
    src/main_window.h
    src/ui/button.h
    src/ui/pixel.h
    src/ui/color.h
    src/nn/neural.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

include_directories(${OpenCV_INCLUDE_DIRS})