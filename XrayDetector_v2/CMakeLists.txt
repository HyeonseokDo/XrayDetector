#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.16...3.27)
project(XrayDetector)
#----------------------------------------------------------------------------

set(CMAKE_OSX_SYSROOT /Library/Developer/CommandLineTools/SDKs/MacOSX15.0.sdk)
set(Geant4_DIR "/Users/do/Desktop/lab/geant4/install/lib/cmake/Geant4")
set(Geant4_INCLUDE_DIRS /Library/Developer/CommandLineTools/SDKs/MacOSX15.0.sdk/usr/include)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
#----------------------------------------------------------------------------
# Find ROOT package
#find_package(ROOT REQUIRED)
#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
include(${Geant4_USE_FILE})
#include(${ROOT_USE_FILE})
#include_directories(${ROOT_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
add_executable(XrayDetector main.cc ${sources} ${headers})
target_link_libraries(XrayDetector ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build XrayDetector. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
set(XRAYDETECTOR_SCRIPTS
 # debug.mac
  init_vis.mac
  vis.mac
  run.mac
  )

foreach(_script ${XRAYDETECTOR_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#add_custom_target(XrayDetector DEPENDS XrayDetector)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
install(TARGETS XrayDetector DESTINATION bin)

