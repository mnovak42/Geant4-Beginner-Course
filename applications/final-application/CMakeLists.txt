#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(yourApplication)


#----------------------------------------------------------------------------
# Find Geant4 package, no UI and Visualization drivers activated
#
## find_package(Geant4 REQUIRED)
#----------------------------------------------------------------------------
# Find Geant4 package, with UI and Visualization drivers activated
#
find_package(Geant4 REQUIRED ui_all vis_all)


#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})


#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executables, and link it to the Geant4 libraries
#
add_executable(yourMainApplication yourMainApplication.cc ${sources} ${headers})
target_link_libraries(yourMainApplication ${Geant4_LIBRARIES} )
