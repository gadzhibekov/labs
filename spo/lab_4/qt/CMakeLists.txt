cmake_minimum_required(VERSION 3.10)

project(app)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

find_package(PkgConfig REQUIRED)


# Найдите библиотеки Qt5
find_package(Qt5 COMPONENTS Widgets Gui Core REQUIRED)

# Включите директории для заголовков и библиотек Qt
find_library(/usr/lib/x86_64-linux-gnu/)
find_library(/usr/lib/x86_64-linux-gnu/)

# Найдите библиотеку SQLite и путь к заголовкам
find_library(SQLITE3_LIB sqlite3)
include_directories(/home/beibala/sqlite/SQLiteCpp/sqlite3/)

# Создание исполняемого файла
add_executable(app main.cpp main_window.cpp ../db.cpp)

# Линковка с библиотеками
target_link_libraries(app ${SQLITE3_LIB} Qt5::Widgets Qt5::Gui Qt5::Core)