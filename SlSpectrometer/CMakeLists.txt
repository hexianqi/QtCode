cmake_minimum_required(VERSION 3.14)

project(SlSpectrometer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(DESTDIR "../Dest")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${DESTDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DESTDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DESTDIR})
set(LIBRARY_OUTPUT_PATH ${DESTDIR})

configure_file(HConfig.h.in HConfig.h)

add_library(${PROJECT_NAME} SHARED
  HSpectrometerGlobal.h
  HSpectrometerAlgorithm.cpp
  HSpectrometerAlgorithm.h
  HSpectrometerCalibrate.cpp
  HSpectrometerCalibrate.h
  HSpectrometerData.h
  HSpectrometerHelper.cpp
  HSpectrometerHelper.h
  HSpectrometerProtocol.cpp
  HSpectrometerProtocol.h
  HSpectrometerTest.cpp
  HSpectrometerTest.h
  HSpectrometer.cpp
  HSpectrometer.h
  HCie.cpp
  HCie.h
  HUsbPortCy.cpp
  HUsbPortCy.h
  HConfig.h
  CCyUSB.cpp
  CCyUSB.h
)

target_compile_definitions(${PROJECT_NAME} PRIVATE SLSPECTROMETER_LIBRARY)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})


