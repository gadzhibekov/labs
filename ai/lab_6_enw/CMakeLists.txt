cmake_minimum_required(VERSION 3.10)

project(lab_6 VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
 
find_package(Qt5 COMPONENTS Core Gui Widgets Network REQUIRED)

include_directories(src)

set(SOURCES
    main.cpp
)

set(HEADERS
    
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)