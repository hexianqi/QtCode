cmake_minimum_required(VERSION 3.14)

project(SlSpectrometer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(SlSpectrometer SHARED
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

target_compile_definitions(SlSpectrometer PRIVATE SLSPECTROMETER_LIBRARY)
