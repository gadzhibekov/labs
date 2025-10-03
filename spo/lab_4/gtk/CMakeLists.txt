cmake_minimum_required(VERSION 3.10)

project(app)

set(CMAKE_CXX_STANDARD 11)

# Изменение компилятора на mingw
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Добавление флага для предупреждений
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

# Поиск пакетов
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# Выбор подходящей library для библиотеки SQLite
find_library(SQLITE3_LIB sqlite3)

# Добавление исполняемого файла с названием app
add_executable(app main.cpp ../db.cpp)

# Компиляция с использованием Gtk и SQLite
target_compile_options(app PRIVATE ${GTK3_CFLAGS})
target_link_libraries(app ${GTK3_LIBRARIES} ${SQLITE3_LIB})