




cmake_minimum_required(VERSION 3.16)

# Укажите имя проекта
project(lab_4 VERSION 1.0 LANGUAGES CXX)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найдите необходимые компоненты Qt
find_package(Qt6 REQUIRED COMPONENTS Core Quick QuickControls2)



set(SOURCES
    src/main.cpp
    src/item.cpp
)

set(HEADERS
    src/item.h
)


# Добавьте исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключите библиотеки Qt
target_link_libraries(SimpleQmlApp PRIVATE Qt5::Core Qt5::Quick Qt5::QuickControls2)

# Укажите записи ресурсов для QML
set(QML_FILES main.qml)
qt_add_qml_module(SimpleQmlApp
    URI SimpleQmlApp
    QML_FILES ${QML_FILES}
)

# Включите Авто-MOC для обработки метаобъектов
set(CMAKE_AUTOMOC ON)
# Включите Авто-Управление ресурсами для QML
set(CMAKE_AUTORCC ON)
