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

option(Q_CC_MSVC "Use Visual C++ compiled" OFF)
option(H_THREAD_COMM "Use Thread Communicate" ON)
option(H_USE_SPEC "Use Spec" OFF)

include_directories("D:/Qt/modules/gsl/win32/include")
link_directories("D:/Qt/modules/gsl/win32/lib")
link_libraries(gsl gslcblas)

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
  HIesTm30.cpp
  HIesTm30.h
  HUsbPortCy.cpp
  HUsbPortCy.h
  HData_CIE_DAY.cpp
  HData_CIE_TC_32.cpp
  HData_CIE_UCS.cpp
  HData_CIE_UCS_P.cpp
  HData_CIE1931.cpp
  HData_CIE1964.cpp
  HData_CIE_IES.cpp
  HData_PhotopicVision.cpp
  HData.h
  HConfig.h
  CCyUSB.cpp
  CCyUSB.h
  SongLang.cpp
  SongLang.h
)

target_compile_definitions(${PROJECT_NAME} PRIVATE SLSPECTROMETER_LIBRARY)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})
