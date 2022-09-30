cmake_minimum_required(VERSION 3.5)

project(SlSpectrometerDemo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DESTDIR "../Dest")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${DESTDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DESTDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DESTDIR})
set(LIBRARY_OUTPUT_PATH ${DESTDIR})

include_directories(..)
link_directories(${DESTDIR})
link_libraries(HeCored HeDatad HeControllerd HePlugind SlSpectrometer)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Widgets Charts)

add_executable(${PROJECT_NAME}
    main.cpp
    HMainWindowDemo.cpp
    HMainWindowDemo.h
    HMainWindowDemo.ui
    HMainWindowDemo_p.h
    HThreadDemo.cpp
    HThreadDemo.h
    HThreadDemo_p.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Charts)
