# \file     CMakeLists.txt
# \author   Thibaut Mattio <thibaut.mattio@gmail.com>
# \date     08/05/2015
# \copyright    2015 Club SONIA AUV, ETS. All rights reserved.
# Use of this source code is governed by the MIT license that can be
# found in the LICENSE file.

#===============================================================================
# G L O B A L   P R O J E C T   C O N F I G U R A T I O N

cmake_minimum_required(VERSION 3.0.2)

project(provider_thruster)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING
            "Choose the type of build: None Debug Release RelWithDebInfo MinSizeRel."
            FORCE)
endif (NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -Wall -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -O3 -s -Wno-unknown-pragmas")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

set(provider_thruster_SRC_DIR "src")

#===============================================================================
# C A T K I N   C O N F I G U R A T I O N

find_package(catkin REQUIRED COMPONENTS
        roscpp
        std_msgs
        sonia_common
        geometry_msgs
        )

catkin_package(
        INCLUDE_DIRS ${provider_thruster_SRC_DIR}
        LIBRARIES
        CATKIN_DEPENDS
        roscpp
        std_msgs
        sonia_common
)

#===============================================================================
# I N C L U D E   F I L E S

file(GLOB_RECURSE provider_thruster_FILES
        "${provider_thruster_SRC_DIR}/*.cc"
        "${provider_thruster_SRC_DIR}/*.h")

list(REMOVE_ITEM provider_thruster_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/${provider_thruster_SRC_DIR}/${PROJECT_NAME}/main.cc)

include_directories(
        ${catkin_INCLUDE_DIRS}
        ${provider_thruster_SRC_DIR}
)
#===============================================================================
# C R E A T E   E X E C U T A B L E

add_executable(${PROJECT_NAME}_node
        ${provider_thruster_SRC_DIR}/${PROJECT_NAME}/main.cc
        ${provider_thruster_SRC_DIR}/${PROJECT_NAME}/provider_thruster_node.cc
        )


target_link_libraries(provider_thruster_node
        ${catkin_LIBRARIES}
        )

add_dependencies(${PROJECT_NAME}_node ${catkin_EXPORTED_TARGETS})

#============================================================================
# U N I T   T E S T S

# Uncomment this line to compile UT.
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
#if (${CATKIN_ENABLE_TESTING})
#    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
#endif ()


