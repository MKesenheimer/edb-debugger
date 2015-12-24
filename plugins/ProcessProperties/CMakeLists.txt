cmake_minimum_required (VERSION 3.0)
include("GNUInstallDirs")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Core)

if(Qt5Core_FOUND)
    find_package(Qt5 5.0.0 REQUIRED Widgets Network)
else(Qt5Core_FOUND)
	find_package(Qt4 4.6.0 REQUIRED QtGui QtNetwork)
endif()

include_directories(
	"${PROJECT_SRC_DIR}/include"
)

# we put the header files from the include directory here 
# too so automoc can "just work"
add_library(ProcessProperties SHARED
	DialogProcessProperties.cpp
	DialogProcessProperties.h
	DialogStrings.cpp
	DialogStrings.h
	ProcessProperties.cpp
	ProcessProperties.h
)

if(Qt5Core_FOUND)
	target_link_libraries(ProcessProperties Qt5::Widgets Qt5::Network)
else(Qt5Core_FOUND)
	target_link_libraries(ProcessProperties Qt4::QtGui Qt4::QtNetwork)
endif()

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
install (TARGETS ProcessProperties DESTINATION ${CMAKE_INSTALL_LIBDIR}/edb)